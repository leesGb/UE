echo on
set base_dir=%~dp0
%base_dir:~0,2%
cd %base_dir%ThirdParty\Src\build

if exist %base_dir%ThirdParty\Src\build rd /s /q %base_dir%ThirdParty\Src\build
mkdir %base_dir%ThirdParty\Src\build

if exist BatPath.bat call BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G "Visual Studio 12 2013" -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo %base_dir%ThirdParty\Src
) else (
	echo CMAKEPATH not define
)

cd %base_dir%

start "" %base_dir%ThirdParty\Src\build\ThirdParty.sln

pause