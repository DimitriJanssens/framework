Import('env')

SUBDIRS = [
  'collection',
  'documentation',
  'eventbus',
  'json',
  'logging',
  'osa',
  'protocols',
  'reactor',
  'testframework',
  'third-party',
]

env.SConscript(dirs=SUBDIRS, name='SConscript', exports = 'env')
