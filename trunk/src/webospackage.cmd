
set STAGING_DIR=STAGING

rem rd /s /y %STAGING_DIR%
del /f /q *.ipk
md %STAGING_DIR%
rem call buildit.cmd
copy rom %STAGING_DIR%
copy x48 %STAGING_DIR%
copy webosappinfo.json %STAGING_DIR%\appinfo.json
copy icon.png %STAGING_DIR%
echo filemode.755=x48 > %STAGING_DIR%\package.properties
palm-package %STAGING_DIR%
