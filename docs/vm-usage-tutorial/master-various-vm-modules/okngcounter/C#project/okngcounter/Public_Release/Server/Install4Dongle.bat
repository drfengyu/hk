cd /d %~dp0
@echo off
(echo # Authorize type, 0:virbox dongle[default], 1:sentinel soft authorize, 2:virbox soft authorize, 3:virbox network dongle, 4:check all of virbox type[include 0,2,3]. other value:default
echo AuthorizeType = 0
)>temp.txt
move /y temp.txt ServerAuthConfig.ini
