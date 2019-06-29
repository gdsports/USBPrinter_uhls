# USBPrinter driver for USB Host Library for SAMD

This driver is designed to work for small USB thermal printers. Do not expect
this to work for laser or inkjet printers because they require complex software
support.

This has been tested with the USB Host Library for SAMD and the ESC POS Printer
library on an Arduino Zero.

https://github.com/gdsports/USB_Host_Library_SAMD

https://github.com/gdsports/ESC_POS_Printer

The ESC POS library send printer ESC/POS commands for different font sizes,
graphics mode, etc. It is based on the Adafruit Thermal printer library but
modified to work with USB thermal receipt printers. Note different thermal
printers from even if from the same manufacturers implement different subsets
of the ESC POS commands. You will have to find the ones that work on your
printer.

## Related

This driver does not work on the USB Host Shield but the following version does.

https://github.com/gdsports/USBPrinter_uhs2

The following driver works on Teensy 3.6 boards.

https://github.com/gdsports/USBPrinter_t36
