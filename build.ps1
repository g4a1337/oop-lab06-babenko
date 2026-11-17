param([string]$CompilerDirectory = "")
$ErrorActionPreference = "Stop"
if ($CompilerDirectory) {
    $resolvedCompilerDirectory = (Resolve-Path -LiteralPath $CompilerDirectory).Path
    $env:PATH = $resolvedCompilerDirectory + [IO.Path]::PathSeparator + $env:PATH
}
$compiler = (Get-Command g++ -CommandType Application -ErrorAction Stop).Source
Push-Location -LiteralPath $PSScriptRoot
try {
    & $compiler '-std=c++14' '-O2' '-Wall' '-Wextra' '-pedantic' '-DCOMPLEX_EXPORTS' '-c' 'complex.cpp' '-o' 'complex.o'
    if ($LASTEXITCODE -ne 0) { throw 'g++ failed' }
    & $compiler '-shared' 'complex.o' '-Wl,--out-implib,libcomplex.dll.a' '-o' 'complex.dll'
    if ($LASTEXITCODE -ne 0) { throw 'g++ failed' }
    & $compiler '-std=c++14' '-O2' '-Wall' '-Wextra' '-pedantic' 'main.cpp' '-L.' '-lcomplex' '-o' 'lab06.exe'
    if ($LASTEXITCODE -ne 0) { throw 'g++ failed' }
    Write-Host 'Build completed: lab06.exe'
} finally {
    Pop-Location
}
