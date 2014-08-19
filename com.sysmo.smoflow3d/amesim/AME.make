$(CC) -I$(AME)/lib -c -I$(THISNODE)/../src
$(CC)
-L$(THISNODE)/../bin -lSmoFlow.dll
win32:$(THISNODE)\lib\$(MACHINETYPE)\TPF.lib
win32_intel:$(THISNODE)\lib\$(MACHINETYPE)\TPF.lib
win64:$(THISNODE)\lib\$(MACHINETYPE)\TPF.lib
