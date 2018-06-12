# Specify the path from mdio_out generated on the component clock to the input of the DFF clocked from MDC as false
expr {(!`$EnableExternOE`) ?
   [set_false_path -from [get_pins {\`$CY_FITTER_NAME`:mdio_o\/q}] -to [get_pins {\`$CY_FITTER_NAME`:bMDIO:mdio_reg\/main_0}]] : {}}