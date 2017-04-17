cd BasicEngine
del *.ncb /q
del *.user /q
rd debug /s/q
rd release /s/q
rd debug_unicode /s/q
rd release_unicode /s/q

cd ../NBase
del *.ncb /q
del *.user /q
rd debug /s/q
rd release /s/q
rd debug_unicode /s/q
rd release_unicode /s/q

cd ../NetWork
del *.ncb /q
del *.user /q
rd debug /s/q
rd release /s/q
rd debug_unicode /s/q
rd release_unicode /s/q


cd ../MuGis
del *.ncb /q
del *.user /q
rd debug /s/q
rd release /s/q
rd debug_unicode /s/q
rd release_unicode /s/q


cd ../ExeFiles/debug_tip
del *.* /q
cd ../release_tip
del *.* /q
cd ../
cd ../


cd ./LibFiles/debug_lib
del *.* /q
cd ../release_lib
del *.* /q
cd ../
cd ../

cd ./TestAppMain
del *.ncb /q
del *.user /q
rd debug /s/q
rd release /s/q
rd Debug_Unicode /s/q
rd Release_Unicode /s/q
cd ../

cd VSInstall
rd release /s/q
cd ../

del *.ncb /q








