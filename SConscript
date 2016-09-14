Import('env')

SUBDIRS = [
  'collection',
  'documentation',
  'eventbus',
  'osa',
  'protocols',
  'testframework',
  'third-party',
]

env.SConscript(dirs=SUBDIRS, name='SConscript', exports = 'env')
