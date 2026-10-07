// The website catalogue entry for a promoted release, derived from the release
// record so the site lists the qualified bytes and nothing else. The shape is
// the website's (site/src/lib/releases.ts there), whose releaseErrors() judges
// what `site` writes. The same file in both products apart from the product block.
// Usage: node scripts/website-release.mjs site --record FILE --base-url URL --site DIR --released-at YYYY-MM-DD
import { readFile, writeFile } from 'node:fs/promises';
import { pathToFileURL } from 'node:url';

// The product block.
export const PRODUCT_ID = 'SwankyAmp';
export const PUBLIC_PREFIX = 'swankyamp';
const ID_PREFIX = 'swanky-amp-2';
const JOURNEY = 'free';
const LICENSE_SUMMARY = 'Free and open source under GPLv3 or later.';
const ARTIFACTS = {
  'macos-pkg': {
    slug: 'macos-universal', os: 'macOS', architecture: 'Apple silicon and Intel',
    format: 'CLAP, VST3, Audio Unit and standalone in a signed and notarized .pkg installer',
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

// The rest is the same in both products.
export function downloadEntries(record, { baseUrl }) {
  if (!record.artifacts?.length) throw new Error('The release record names no artifacts.');
  return record.artifacts.map(artifact => {
    const platform = ARTIFACTS[artifact.kind];
    if (!platform) throw new Error(`No catalogue entry is defined for ${artifact.kind}.`);
    return {
      id: `${ID_PREFIX}-${record.version}-${platform.slug}`,
      version: record.version,
      os: platform.os,
      architecture: platform.architecture,
      format: platform.format,
      journey: JOURNEY,
      requirements: platform.requirements,
      bytes: artifact.bytes,
      sha256: artifact.sha256,
      url: `${baseUrl.replace(/\/+$/, '')}/${PUBLIC_PREFIX}/${record.version}/${artifact.name}`,
    };
  });
}

/** The changelog section's lead paragraph, or else its entries run together,
 *  because the catalogue renders release notes as one paragraph. */
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

/** Replace this product's current-release fields and only those: earlier
 *  versions and the other products stay as the catalogue states them. */
export function updatedReleases(catalogue, record, options) {
  const next = structuredClone(catalogue);
  const product = next.products?.find(entry => entry.productId === PRODUCT_ID);
  if (!product) throw new Error(`The catalogue has no ${PRODUCT_ID} release.`);
  product.status = 'available';
  product.version = record.version;
  product.build = record.build;
  product.releasedAt = options.releasedAt;
  product.licenseSummary = LICENSE_SUMMARY;
  product.releaseNotes = options.releaseNotes;
  product.verifiedDownloads = downloadEntries(record, options);
  return next;
}

/** Only an approved host may serve a download, so the base URL's host joins
 *  the list in the change that starts pointing at it. */
export function withDownloadHost(site, baseUrl) {
  const { hostname } = new URL(baseUrl);
  const hosts = site.downloadHosts ?? [];
  return hosts.includes(hostname) ? site : { ...site, downloadHosts: [...hosts, hostname] };
}

const json = async path => JSON.parse(await readFile(path, 'utf8'));
const writeJson = (path, value) => writeFile(path, `${JSON.stringify(value, null, 2)}\n`);

function argument(argv, name) {
  const index = argv.indexOf(`--${name}`);
  if (index < 0 || index + 1 >= argv.length) throw new Error(`--${name} is required.`);
  return argv[index + 1];
}

async function main(argv) {
  if (argv[0] !== 'site') throw new Error('Usage: website-release.mjs site --record FILE --base-url URL --site DIR --released-at DATE');
  const record = await json(argument(argv, 'record'));
  const baseUrl = argument(argv, 'base-url');
  const site = argument(argv, 'site');
  const releases = updatedReleases(await json(`${site}/src/data/releases.json`), record, {
    baseUrl,
    releasedAt: argument(argv, 'released-at'),
    releaseNotes: releaseNotesFrom(await readFile('CHANGELOG.md', 'utf8'), record.version),
  });
  const siteData = withDownloadHost(await json(`${site}/src/data/site.json`), baseUrl);
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
