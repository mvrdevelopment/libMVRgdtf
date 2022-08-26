pushd . 

call buildLib_Win.bat Release MT
popd
pushd . 

call buildLib_Win.bat Release MD
popd
pushd . 

call buildLib_Win.bat Debug MD
popd
pushd . 

call buildLib_Win.bat Debug MT
popd
pushd . 

echo FINISHED

pause