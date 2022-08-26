pushd . 

call buildLib_Win.bat Release MT MZ
popd
pushd . 

call buildLib_Win.bat Release MT NoMZ
popd
pushd . 

call buildLib_Win.bat Release MD MZ
popd
pushd . 

call buildLib_Win.bat Release MD NoMZ
popd
pushd .


call buildLib_Win.bat Debug MD MZ
popd
pushd . 

call buildLib_Win.bat Debug MD NoMZ
popd
pushd . 


call buildLib_Win.bat Debug MT MZ
popd
pushd . 

call buildLib_Win.bat Debug MT NoMZ
popd
pushd . 


echo FINISHED

pause