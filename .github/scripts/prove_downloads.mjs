import { createHash } from 'node:crypto';
import { readFile } from 'node:fs/promises';

async function prove(file) {
  const source = new URL(file.url);
  if (source.protocol !== 'https:' || source.hostname !== 'github.com') {
    throw new Error(`Unexpected release URL: ${file.id}`);
  }
  const response = await fetch(file.url, { redirect: 'follow', signal: AbortSignal.timeout(120000) });
  if (response.status !== 200 || !response.body) {
    throw new Error(`Download unavailable: ${file.id} (HTTP ${response.status})`);
  }
  const destination = new URL(response.url);
  if (!['github.com', 'release-assets.githubusercontent.com'].includes(destination.hostname)) {
    throw new Error(`GitHub redirected ${file.id} to an unexpected host.`);
  }
  const hash = createHash('sha256');
  let bytes = 0;
  for await (const chunk of response.body) {
    bytes += chunk.length;
    if (bytes > file.bytes) throw new Error(`Download exceeds declared size: ${file.id}`);
    hash.update(chunk);
  }
  if (bytes !== file.bytes || hash.digest('hex') !== file.sha256) {
    throw new Error(`Download bytes do not match the qualified candidate: ${file.id}`);
  }
  console.log(`${file.url}\n  ${bytes} bytes, ${file.sha256}`);
}

try {
  const downloads = JSON.parse(await readFile(process.argv[2] ?? 'downloads.json', 'utf8'));
  if (!downloads.length) throw new Error('No public downloads to prove.');
  for (const file of downloads) await prove(file);
  console.log(`Proved ${downloads.length} public release assets.`);
} catch (error) {
  console.error(error.message);
  process.exitCode = 1;
}
