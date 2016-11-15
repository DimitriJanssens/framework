def App(env, *nargs, **kwargs):
  env = env.Clone()
  env['CPPPATH'].append(env.Dir('../header').srcnode())

  env.Prepend(_LIBFLAGS="-Wl,--start-group ")  # the trailing space is required
  env.Append(_LIBFLAGS=" -Wl,--end-group")  # the leading space is required

  if env.GetOption('unittests') == True:
    env['CPPPATH'].append([ env.Dir('%s/check' %(env['THIRD_PARTY_INC_DIR'])) ])
    kwargs.get('LIBS').append([ 'testframework', 'check', 'gcov' ])

  for f in kwargs.get('LIBS'):
    if 'osthreading' in f:
      kwargs.get('LIBS').append(['pthread'])
      break

  _bin = env.Program(*nargs, LIBPATH = [ env['LIB_DIR'] , env['THIRD_PARTY_LIB_DIR'] ], **kwargs)
  _bin = env.Install(env['BIN_DIR'], _bin)
  return _bin

def Lib(env, *nargs, **kwargs):
  env = env.Clone()
  env['CPPPATH'].append(env.Dir('../header').srcnode())

  if env.GetOption('unittests') == True:
    env['CPPPATH'].append(env.Dir('../../header').srcnode())
    env['CPPPATH'].append([ env.Dir('%s/check' %(env['THIRD_PARTY_INC_DIR'])) ])

  _lib = env.StaticLibrary(*nargs, **kwargs)
  _lib = env.Install(env['LIB_DIR'], _lib)
  return _lib
