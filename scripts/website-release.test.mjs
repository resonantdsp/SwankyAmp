// The promotion's last step edits the website's published catalogue, so the
// entries must describe the qualified bytes at their public URLs and leave
// everything else in the catalogue alone.
import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import {
  PRODUCT_ID, PUBLIC_PREFIX, downloadEntries, releaseNotesFrom, updatedReleases, withDownloadHost,
} from './website-release.mjs';

const record = JSON.parse(await readFile(new URL('./fixtures/release-record.json', import.meta.url), 'utf8'));
const baseUrl = 'https://downloads.example.test';
const options = { baseUrl, releasedAt: '2026-10-30', releaseNotes: 'Notes.' };
const catalogue = { schemaVersion: 1, products: [
  { productId: PRODUCT_ID, status: 'recovering', verifiedDownloads: [], legacy: [{ version: '1.0.0' }] },
  { productId: 'Other', status: 'recovering', verifiedDownloads: [] },
] };

test('each recorded artifact becomes a download of the same bytes at its public URL', () => {
  const entries = downloadEntries(record, options);
  assert.equal(new Set(entries.map(entry => entry.id)).size, record.artifacts.length);
  for (const [index, artifact] of record.artifacts.entries()) {
    assert.equal(entries[index].version, record.version);
    assert.equal(entries[index].bytes, artifact.bytes);
    assert.equal(entries[index].sha256, artifact.sha256);
    assert.equal(entries[index].url, `${baseUrl}/${PUBLIC_PREFIX}/${record.version}/${artifact.name}`);
  }
  assert.throws(() => downloadEntries({ ...record, artifacts: [{ ...record.artifacts[0], kind: 'unknown' }] }, options));
  assert.throws(() => downloadEntries({ ...record, artifacts: [] }, options));
});

test('the product becomes available with its build and keeps its earlier versions and the other products', () => {
  const next = updatedReleases(catalogue, record, options);
  const [product, other] = next.products;
  assert.equal(product.status, 'available');
  assert.equal(product.version, record.version);
  assert.equal(product.build, record.build);
  assert.equal(product.releasedAt, options.releasedAt);
  assert.deepEqual(product.legacy, catalogue.products[0].legacy);
  assert.deepEqual(other, catalogue.products[1]);
  assert.deepEqual(catalogue.products[0].verifiedDownloads, [], 'the input catalogue is not changed');
});

test('release notes come from the changelog and the download host joins the approved hosts once', () => {
  const changelog = [
    '# Changelog', '', '## Unreleased', '', '## 2.0.0 — 2026-10-30', '',
    'Version 2 opens a new line.', 'It is a rebuild.', '', '- A detail.', '', '## 1.0.0 — 2024-01-01', '', '- Older.',
  ].join('\n');
  assert.equal(releaseNotesFrom(changelog, '2.0.0'), 'Version 2 opens a new line. It is a rebuild.');
  assert.equal(releaseNotesFrom(changelog, '1.0.0'), 'Older.');
  assert.throws(() => releaseNotesFrom(changelog, '9.9.9'));
  assert.deepEqual(withDownloadHost({ downloadHosts: [] }, baseUrl).downloadHosts, ['downloads.example.test']);
  assert.deepEqual(withDownloadHost({ downloadHosts: ['downloads.example.test'] }, baseUrl).downloadHosts, ['downloads.example.test']);
});
