del *.ncb /q

cd DataManger
del *.ncb /q
rd debug /s/q
rd release /s/q
cd ../

cd commserver
del *.ncb /q
rd debug /s/q
rd release /s/q
cd ../

cd mainpro
del *.ncb /q
rd debug /s/q
rd release /s/q
cd ../

cd ExeFiles

cd Debug_tip
del *.ilk /q
del *.exe /q
del *.dll /q
cd logs
del *.* /q
cd ../
cd ../

cd release_tip
del *.exe /q
del *.dll /q
cd logs
del *.* /q
cd ../
cd ../

