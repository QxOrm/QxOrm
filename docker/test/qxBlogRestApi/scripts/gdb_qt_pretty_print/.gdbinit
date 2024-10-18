python

import sys, os.path
sys.path.insert(0, os.path.expanduser("~/scripts/gdb_qt_pretty_print"))

from qt import register_qt_printers
register_qt_printers (None)

end
