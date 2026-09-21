// Derive the public Free catalogue entry from the exact qualified candidate.
import { readFile, writeFile } from 'node:fs/promises';
import { pathToFileURL } from 'node:url';

export const PRODUCT_ID = 'SwankyAmp';
export const DEFAULT_LICENSE_SUMMARY = 'Free and open source under GPLv3 or later.';

const ARTIFACTS = {
  'macos-pkg': {
    slug: 'macos-universal', os: 'macOS', architecture: 'Apple silicon and Intel',
    format: 'CLAP, VST3 and standalone in a signed and notarized .pkg installer',
    requirements: 'macOS 11 or later',
  },
  'windows-exe': {
    slug: 'windows-x64', os: 'Windows', architecture: 'x64',
    format: 'CLAP, VST3 and standalone in a signed .exe installer',
    requirements: 'Windows 10 or later, 64-bit',
  },
  'linux-tarball': {
    slug: 'linux-x64', os: 'Linux', architecture: 'x64',
    format: 'CLAP, VST3 and standalone in a .tar.gz bundle',
    requirements: 'Ubuntu 22.04 or a compatible x64 Linux distribution',
  },
};

export function publicUrl(repository, tag, name) {
  return `${repository.replace(/\/+$/, '')}/releases/download/${tag}/${name}`;
}

export function downloadEntries(record, { repository, tag }) {
  if (!record.version) throw new Error('The release record has no version.');
  if (tag !== `v${record.version}`) throw new Error(`${tag} does not name version ${record.version}.`);
  if (!Array.isArray(record.artifacts) || !record.artifacts.length) {
    throw new Error('The release record names no artifacts.');
  }
  return record.artifacts.map(artifact => {
    const platform = ARTIFACTS[artifact.kind];
    if (!platform) throw new Error(`No catalogue entry is defined for ${artifact.kind}.`);
    return {
      id: `swanky-amp-2-${record.version}-${platform.slug}`,
      version: record.version,
      os: platform.os,
      architecture: platform.architecture,
      format: platform.format,
      journey: 'free',
      requirements: platform.requirements,
      bytes: artifact.bytes,
      sha256: artifact.sha256,
      url: publicUrl(repository, tag, artifact.name),
    };
  });
}

export function releaseNotesFrom(changelog, version) {
  const heading = new RegExp(`^## ${version.replace(/\./g, '\\.')}(?:\\s|$)`);
  const lines = changelog.split('\n');
  const start = lines.findIndex(line => heading.test(line));
  if (start < 0) throw new Error(`CHANGELOG.md has no '## ${version}' section.`);
  const body = [];
  for (const line of lines.slice(start + 1)) {
    if (/^## /.test(line)) break;
    body.push(line);
  }
  const paragraph = [];
  for (const line of body) {
    if (/^\s*-\s/.test(line)) break;
    if (!line.trim()) {
      if (paragraph.length) break;
      continue;
    }
    paragraph.push(line.trim());
  }
  if (paragraph.length) return paragraph.join(' ');
  const entries = [];
  let current;
  for (const line of body) {
    if (/^\s*-\s/.test(line)) {
      if (current) entries.push(current);
      current = line.replace(/^\s*-\s/, '').trim();
    } else if (current && line.trim()) current += ` ${line.trim()}`;
  }
  if (current) entries.push(current);
  if (!entries.length) throw new Error(`The '## ${version}' changelog section is empty.`);
  return entries.join(' ');
}

export function updatedReleases(catalogue, record, options) {
  const next = structuredClone(catalogue);
  const product = next.products?.find(entry => entry.productId === PRODUCT_ID);
  if (!product) throw new Error(`The catalogue has no ${PRODUCT_ID} release.`);
  product.status = 'available';
  product.version = record.version;
  product.releasedAt = options.releasedAt;
  product.licenseSummary = options.licenseSummary ?? DEFAULT_LICENSE_SUMMARY;
  product.releaseNotes = options.releaseNotes;
  product.verifiedDownloads = downloadEntries(record, options);
  return next;
}

export function withDownloadHost(site, repository) {
  const { hostname } = new URL(repository);
  const hosts = site.downloadHosts ?? [];
  return hosts.includes(hostname) ? site : { ...site, downloadHosts: [...hosts, hostname] };
}

const json = async path => JSON.parse(await readFile(path, 'utf8'));
const writeJson = (path, value) => writeFile(path, `${JSON.stringify(value, null, 2)}\n`);

function argument(argv, name, required = true) {
  const index = argv.indexOf(`--${name}`);
  if (index < 0 || index + 1 >= argv.length) {
    if (required) throw new Error(`--${name} is required.`);
    return undefined;
  }
  return argv[index + 1];
}

async function main(argv) {
  const command = argv[0];
  const record = await json(argument(argv, 'record'));
  const repository = argument(argv, 'repository');
  const tag = argument(argv, 'tag');
  const options = { repository, tag };
  if (command === 'downloads') {
    process.stdout.write(`${JSON.stringify(downloadEntries(record, options), null, 2)}\n`);
    return;
  }
  if (command !== 'site') {
    throw new Error('Usage: website_release.mjs downloads|site --record FILE --repository URL --tag TAG ...');
  }
  const site = argument(argv, 'site');
  const releasedAt = argument(argv, 'released-at');
  const changelog = argument(argv, 'changelog', false) ?? 'CHANGELOG.md';
  const releases = updatedReleases(await json(`${site}/src/data/releases.json`), record, {
    ...options,
    releasedAt,
    releaseNotes: releaseNotesFrom(await readFile(changelog, 'utf8'), record.version),
  });
  const siteData = withDownloadHost(await json(`${site}/src/data/site.json`), repository);
  await writeJson(`${site}/src/data/releases.json`, releases);
  await writeJson(`${site}/src/data/site.json`, siteData);

  const { releaseErrors } = await import(pathToFileURL(`${site}/src/lib/releases.ts`).href);
  const product = releases.products.find(entry => entry.productId === PRODUCT_ID);
  const errors = releaseErrors(product, siteData.downloadHosts ?? []);
  if (errors.length) throw new Error(`The website would reject this release: ${errors.join('; ')}`);
  console.log(`Catalogued ${PRODUCT_ID} ${record.version} with ${product.verifiedDownloads.length} downloads.`);
}

if (process.argv[1] && import.meta.url === pathToFileURL(process.argv[1]).href) {
  try { await main(process.argv.slice(2)); }
  catch (error) { console.error(error.message); process.exitCode = 1; }
}
