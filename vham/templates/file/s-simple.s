@
@ Author:
@ Date..:
@
    .CODE 32
@    .SECTION .iwram
@    .SECTION .ewram
    .GLOBAL  TheName
    .TYPE    TheName, function
    .ALIGN

TheName:
    @ Save registers on stack
    STMFD   sp!, {r?-r?}


    @ Load registers from stack
    LDMFD   sp!, {r?-r?}
    BX      lr
@
@ End
@











@ END OF FILE
