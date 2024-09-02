@echo off
echo ---------------------------------
rem 获取模块名称
echo %~dp0
cd %~dp0
for %%i in (%cd%) do set moduName=%%~ni
echo moduName:%moduName%

cd..
cd..

set xmlpath=%cd%\%moduName%\
echo xmlPath:%xmlpath%

echo xcopy "%~dp0x64\Release\*.dll" "%xmlpath%" /y
xcopy "%~dp0x64\Release\*.dll" "%xmlpath%" /y

echo xcopy "%~dp0x64\Release\*.pdb" "%xmlpath%" /y
xcopy "%~dp0x64\Release\*.pdb" "%xmlpath%" /y
@echo ---------------------------------
pause 