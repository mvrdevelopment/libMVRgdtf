pushd . 

call buildLib_Win.bat Release MT MZ false
popd
pushd . 

call buildLib_Win.bat Release MT NoMZ false
popd
pushd . 

call buildLib_Win.bat Release MD MZ false
popd
pushd . 

call buildLib_Win.bat Release MD NoMZ false
popd
pushd .

call buildLib_Win.bat Debug MD MZ false
popd
pushd . 

call buildLib_Win.bat Debug MD NoMZ false
popd
pushd . 

call buildLib_Win.bat Debug MT MZ false
popd
pushd . 

call buildLib_Win.bat Debug MT NoMZ false
popd
pushd . 

echo FINISHED

pause