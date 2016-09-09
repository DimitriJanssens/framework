def App(env, *nargs, **kwargs):
	cpenv = env.Clone()
	cpenv['CPPPATH'].append(cpenv.Dir('../header').srcnode().abspath)

	cpenv.Prepend(_LIBFLAGS="-Wl,--start-group ")  # the trailing space is required
	cpenv.Append(_LIBFLAGS=" -Wl,--end-group")  # the trailing space is required

	if cpenv.GetOption('unittests') == True:
		cpenv['CPPPATH'].append([ '%s/check' %(cpenv['INC_DIR']) ])
		kwargs.get('LIBS').append([ 'testframework', 'check', 'gcov' ])

	for f in kwargs.get('LIBS'):
		if 	'osthreading' in f:
			kwargs.get('LIBS').append(['pthread'])	

	_bin = cpenv.Program(*nargs, LIBPATH = cpenv['LIB_DIR'], **kwargs)
	_bin = cpenv.Install(cpenv['BIN_DIR'], _bin)
	return _bin

def Lib(env, *nargs, **kwargs):
	cpenv = env.Clone()
	cpenv['CPPPATH'].append(cpenv.Dir('../header').srcnode().abspath)

	if cpenv.GetOption('unittests') == True:
		cpenv['CPPPATH'].append(cpenv.Dir('../../header').srcnode().abspath)
		cpenv['CPPPATH'].append(['%s/check' %(cpenv['INC_DIR'])])

	_lib = cpenv.StaticLibrary(*nargs, **kwargs)
	_lib = cpenv.Install(cpenv['LIB_DIR'], _lib)
	return _lib