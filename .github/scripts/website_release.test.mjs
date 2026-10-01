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
// The website catalogue's shape (web/site/src/lib/releases.ts): earlier
// versions live under `legacy`, each with its own downloads.
const catalogue = { schemaVersion: 1, products: [
  { productId: 'SwankyAmpPro', status: 'recovering', source: 'records', verifiedDownloads: [] },
  {
    productId: 'SwankyAmp', status: 'recovering', source: 'archived free-product page',
    verifiedDownloads: [],
    legacy: [{
      version: '1.4.0', replacedBy: '2.0',
      license: 'Free and open source under the GNU General Public License v3 or later.',
      formats: ['Windows: VST3 installer and VST3 file'],
      source: 'The archived site\'s v1.4.0 downloads.',
      verifiedDownloads: [{
        id: 'swanky-amp-1.4.0-windows', version: '1.4.0', os: 'Windows', architecture: 'x64',
        format: 'Installer: VST3', journey: 'free', requirements: 'Windows 10 or later',
        bytes: 2486272, sha256: 'd'.repeat(64),
        url: 'https://downloads.resonantdsp.com/swankyamp/1.4.0/SwankyAmp-1.4.0-windows.msi',
      }],
    }],
  },
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
    'a release without Linux has no Linux catalogue entry',
  );
  assert.throws(() => downloadEntries(record, { ...options, tag: 'v2.0.1' }));
});

test('cataloguing version 2 keeps the 1.4 legacy release and other products', () => {
  const next = updatedReleases(catalogue, record, options);
  const free = next.products[1];
  assert.equal(free.status, 'available');
  assert.equal(free.version, '2.0.0');
  assert.equal(free.releasedAt, options.releasedAt);
  assert.deepEqual(free.legacy, catalogue.products[1].legacy);
  assert.deepEqual(next.products[0], catalogue.products[0]);
  assert.equal(catalogue.products[1].status, 'recovering');
});

test('release notes and the GitHub download host are derived without replacing existing hosts', () => {
  const changelog = '# Changelog\n\n## 2.0.0 — 2026-09-20\n\nVersion 2 is here.\n\n- Detail.\n';
  assert.equal(releaseNotesFrom(changelog, '2.0.0'), 'Version 2 is here.');
  assert.throws(() => releaseNotesFrom(changelog, '2.0.1'));
  assert.deepEqual(
    withDownloadHost({ downloadHosts: ['downloads.example.test'] }, options.repository).downloadHosts,
    ['downloads.example.test', 'github.com'],
  );
});
