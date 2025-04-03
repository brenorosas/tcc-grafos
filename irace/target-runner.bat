@echo off
::##############################################################################
:: BAT version of target-runner for Windows.
:: Adapted for the TCC-Grafos project
::##############################################################################

:: Set the base directory for executables
SET "base_dir=%~dp0.."
SET "exe=%base_dir%\grasp.exe"
SET "fixed_params= "

FOR /f "tokens=1-4*" %%a IN ("%*") DO (
	SET candidate=%%a
	SET instance_id=%%b
	SET seed=%%c
	SET instance=%%d
	SET candidate_parameters=%%e
)

SET "stdout=c%candidate%-%instance_id%-%seed%.stdout"
SET "stderr=c%candidate%-%instance_id%-%seed%.stderr"

:: Run the algorithm with the given parameters
%exe% %fixed_params% -i %instance% --seed %seed% %candidate_parameters% > %stdout% 2> %stderr%

:: Read the cost from the output file
:: Assuming the cost is printed in the format "Cost: X" in the last line
for /f "tokens=2" %%a in ('type %stdout% ^| findstr /i "Cost:"') do set COST=%%a

:: If no cost was found, exit with error
if not defined COST (
	echo Error: No cost value found in output
	exit 1
)

:: Output the cost
echo %COST%

:: Clean up temporary files
del %stdout% %stderr%

exit 0
