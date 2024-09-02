@echo off
echo ---------------------------------
rem 获取模块名称
echo %~dp0
cd %~dp0
for %%i in (%cd%) do set prjName=%%~ni
echo prjName:%prjName%
set moduName=%prjName:~0,-7%
echo moduName:%moduName%

cd..
cd..
cd..

set xmlpath=%cd%\%moduName%\
echo xmlPath:%xmlpath%

echo xcopy "%~dp0bin\Release\%prjName%.dll" "%xmlpath%" /y
xcopy "%~dp0bin\Release\%prjName%.dll" "%xmlpath%" /y

echo xcopy "%~dp0bin\Release\%prjName%.pdb" "%xmlpath%" /y
xcopy "%~dp0bin\Release\%prjName%.pdb" "%xmlpath%" /y
@echo ---------------------------------
pause 