@echo off
setlocal enabledelayedexpansion
for %%f in (%OBJS%) do (
    if exist %%f del %%f
)
