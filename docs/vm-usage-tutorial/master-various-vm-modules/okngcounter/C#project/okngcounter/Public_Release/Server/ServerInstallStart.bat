@rem 注释：切换到当前路径
cd /d %~dp0
@rem 注释：从配置文件中提取服务名称
set ServiceName=VisionMasterServer
for /f "tokens=1,2* delims== " %%a in (ServerConfiguration.ini) do (
@ if "%%a"=="ServiceName" (set ServiceName=%%b 
@ goto end )
 )

:end
@rem 注释：卸载服务
@net stop %ServiceName%
@sc delete %ServiceName%

@rem 注释：安装服务
start /b /wait VisionMasterServer.exe -i
@net start %ServiceName%
