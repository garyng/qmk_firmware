[CmdletBinding()]
param (
    [Parameter(Mandatory=$true, Position=0)]
    [string]
    $reportDescriptor
)

docker run --rm garyng/hidrdd-docker ./rd.rex -c "$reportDescriptor" | Set-Content output.c
