import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { downloadEntries, releaseNotesFrom, updatedReleases, withDownloadHost } from './website_release.mjs';

const record = JSON.parse(await readFile(new URL('./fixtures/release-record.json', import.meta.url)));
const options = {
  repository: 'https://github.com/resonantdsp/SwankyAmp',
  tag: 'v2.0.0',
  releasedAt: '2026-09-20',
  releaseNotes: 'Version 2 keeps the released sound in a new host identity.',
};
const catalogue = { schemaVersion: 1, products: [
  {
    productId: 'SwankyAmp', status: 'recovering', historicalVersion: '1.4.0',
    historicalPlatforms: ['Windows: VST3', 'macOS: VST3 and Audio Units'],
    historicalLicense: 'Free and open source under GPLv3.', source: 'archive',
    verifiedDownloads: [], releaseNotes: 'Being verified.',
  },
  { productId: 'SwankyAmpPro', status: 'recovering', verifiedDownloads: [] },
] };

test('qualified artifacts become stable free downloads with the version 2 identity', () => {
  const downloads = downloadEntries(record, options);
  assert.deepEqual(downloads.map(file => file.id), [
    'swanky-amp-2-2.0.0-macos-universal',
    'swanky-amp-2-2.0.0-windows-x64',
    'swanky-amp-2-2.0.0-linux-x64',
  ]);
  assert.deepEqual(downloads.map(file => file.journey), ['free', 'free', 'free']);
  for (const [index, file] of downloads.entries()) {
    assert.equal(file.bytes, record.artifacts[index].bytes);
    assert.equal(file.sha256, record.artifacts[index].sha256);
    assert.match(file.url, /^https:\/\/github\.com\/resonantdsp\/SwankyAmp\/releases\/download\/v2\.0\.0\//);
  }
  const withoutLinux = { ...record, artifacts: record.artifacts.filter(file => file.kind !== 'linux-tarball') };
  assert.deepEqual(
    downloadEntries(withoutLinux, options).map(file => file.id),
    ['swanky-amp-2-2.0.0-macos-universal', 'swanky-amp-2-2.0.0-windows-x64'],
    'a failed Linux attempt does not create a Linux catalogue entry',
  );
  assert.throws(() => downloadEntries(record, { ...options, tag: 'v2.0.1' }), /does not name version/);
});

test('cataloguing version 2 preserves the 1.4 archive and other products', () => {
  const next = updatedReleases(catalogue, record, options);
  const free = next.products[0];
  assert.equal(free.status, 'available');
  assert.equal(free.version, '2.0.0');
  assert.equal(free.historicalVersion, '1.4.0');
  assert.deepEqual(free.historicalPlatforms, catalogue.products[0].historicalPlatforms);
  assert.equal(free.historicalLicense, catalogue.products[0].historicalLicense);
  assert.equal(free.source, catalogue.products[0].source);
  assert.deepEqual(next.products[1], catalogue.products[1]);
  assert.equal(catalogue.products[0].status, 'recovering');
});

test('release notes and the GitHub download host are derived without replacing existing hosts', () => {
  const changelog = '# Changelog\n\n## 2.0.0 — 2026-09-20\n\nVersion 2 is here.\n\n- Detail.\n';
  assert.equal(releaseNotesFrom(changelog, '2.0.0'), 'Version 2 is here.');
  assert.throws(() => releaseNotesFrom(changelog, '2.0.1'), /no '## 2\.0\.1' section/);
  assert.deepEqual(
    withDownloadHost({ downloadHosts: ['downloads.example.test'] }, options.repository).downloadHosts,
    ['downloads.example.test', 'github.com'],
  );
});
