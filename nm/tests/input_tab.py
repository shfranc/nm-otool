# Each error message must (at least) contain this kind of line :
# Error line [line]: [message].
# ex : Error line 3: Wrong number of parameters for this intruction.
# This line will be compared. Give the error type and the line of the error in INPUT.

ERROR_TYPE = {
	# "PARAM_NB":			"Wrong number of parameters for this intruction."
}

INPUT = {
	# "file":	{"error": True,  "error_type": "NO_NAME", "error_line": 1},
'32_exe_hard':    {'error': False,  'error_type': None, 'error_line': -1},
'64_bundle':    {'error': False,  'error_type': None, 'error_line': -1},
'64_exe_easy':    {'error': False,  'error_type': None, 'error_line': -1},
'64_exe_hard':    {'error': False,  'error_type': None, 'error_line': -1},
'64_exe_medium':    {'error': False,  'error_type': None, 'error_line': -1},
'64_lib_dynamic_hard':    {'error': False,  'error_type': None, 'error_line': -1},
'64_lib_dynamic_medium':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-OSX-ppc-and-i386-bash':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-OSX-ppc-openssl-1':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-OSX-x64-ls':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-OSX-x86-ls':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-iOS-arm1176JZFS-bash':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-iOS-armv7s-Helloworld':    {'error': False,  'error_type': None, 'error_line': -1},
'fat_hard':    {'error': False,  'error_type': None, 'error_line': -1},
'lib_archive_medium':    {'error': False,  'error_type': None, 'error_line': -1},
'object_easy':    {'error': False,  'error_type': None, 'error_line': -1},
'object_medium':    {'error': False,  'error_type': None, 'error_line': -1},
'test_32':    {'error': False,  'error_type': None, 'error_line': -1},
'test_64':    {'error': False,  'error_type': None, 'error_line': -1},
'MachO-OSX-ppc-openssl-1.0.1h':    {'error': False,  'error_type': None, 'error_line': -1},
}
