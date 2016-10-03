cdef class CPU2A03:
    cdef int A, F, X, Y, P, SP, CYC
    def __cinit__(self):
        self.reset()
    def reset(self):
        self.P = 0xfffc
        self.SP = 0xff
        self.CYC = 0
    def pulse(self):
        if 0 == self.CYC:
            pass
        elif 1 == self.CYC:
            pass
    @staticmethod
    def mask(int op, int one_bits, int zero_bits):
        return (op&one_bits == one_bits) and (not(op)&zero_bits == zero_bits)



cdef int * NESPaletteNTSC = [
        0x7c7c7c,
        0x0000fc,
        0x0000bc,
        0x4428bc,
        0x940084,
        0xa80020,
        0xa81000,
        0x881400,
        0x503000,
        0x007800,
        0x006800,
        0x005800,
        0x004058,
        0x000000,
        0x000000,
        0x000000,
        0xbcbcbc,
        0x0078f8,
        0x0058f8,
        0x6844fc,
        0xd800fc,
        0xe40058,
        0xf83800,
        0xac7c00,
        0x00b800,
        0x00a800,
        0x00a844,
        0x008888,
        0x000000,
        0x000000,
        0x000000,
        0xf8f8f8,
        0x3cbcfc,
        0x6888fc,
        0x9878f8,
        0xf878f8,
        0xf85898,
        0xf87858,
        0xfca044,
        0xf8b800,
        0xb8f818,
        0x58d854,
        0x58f898,
        0x00e8d8,
        0x787878,
        0x000000,
        0x000000,
        0xfcfcfc,
        0xa4e4fc,
        0xb8b8f8,
        0xd8b8f8,
        0xf8b8f8,
        0xf8a4c0,
        0xf0d0b0,
        0xfce0a8,
        0xf8d878,
        0xd8f878,
        0xb8f8b8,
        0xb8f8d8,
        0x00fcfc,
        0xf8d8f8,
        0x000000,
        0x000000
    ]
cdef class NESRasterizerNTSC:
    cdef int * PALETTE
    cdef int _PPUCTRL, _PPUMASK, _OAMADDR
    cdef int bgscrollx, bgscrolly, linecounter, linespritecounter, sprite0
    cdef int bgscrolllatch, addresslatch
    cdef int ppuaddress, oamaddress, spritelimit
    cdef int OAM[256]

    def __cinit__(self):
        self.PALETTE = NESPaletteNTSC
        self._PPUCTRL = 0
        self._PPUMASK = 0
        self._OAMADDR = 0
        self.bgscrollx = 0
        self.bgscrolly = 0
        self.linecounter = 0
        self.linespritecounter = 0
        self.sprite0 = False
        self.bgscrolllatch = 0
        self.addresslatch = 0
        self.ppuaddress = 0
        self.oamaddress = 0
        self.spritelimit = True
    def PPUCTRL(self, int data):
        self._PPUCTRL = data & 255
    def PPUMASK(self, int data):
        self._PPUMASK = data & 255
    def OAMADDR(self, int data):
        self._OAMADDR = data & 255
    def PPUDATA(self, int data):
        ppuaddressinc = True if self._PPUCTRL & 4 else False
    def PPUSCROLL(self, int data):
        if self.bgscrolllatch is 1:
            self.bgscrolly = int(data) & 255
            self.bgscrolllatch = 0
        else:
            self.bgscrollx = int(data) & 255
            self.bgscrolllatch = 1
    def PPUADDR(self, int data):
        if self.addresslatch is 1:
            self.ppuaddress = self.ppuaddress & 255 + (int(data) & 0x3f) << 8
            self.addresslatch = 0
        else:
            self.ppuaddress = self.ppuaddress & 0x3f00 + (int(data) & 255)
            self.addresslatch = 1
    def OAMDATA(self, int data):
        self.OAM[self.oamaddress] = data
        self.oamaddress = (self.oamaddress + 1) & 255
    def drawLine(self, mem, linemap, int lineNum):
        cdef int[:] vmem = mem.b
        ppuctrl = self._PPUCTRL
        cdef int nametablebase = ppuctrl & 3
        cdef int nametable = 0x2000+0x400*nametablebase
        cdef int spritebase = 0x1000 if ppuctrl & 8 else 0x0000
        cdef int patternbase = 0x1000 if ppuctrl & 16 else 0x0000
        cdef int spritesize = 16 if ppuctrl & 32 else 8
        cdef int ppumask = self._PPUMASK
        sprites = []
        cdef int spr = 63
        while spr >= 0:
            y = lineNum - self.OAM[spr*4]
            if (y >= 0) and (y < spritesize):
                if spr is 0:
                    self.sprite0 = True
                if self.spritelimit and (len(sprites) > 8):
                    break
                sprites.append([y, self.OAM[spr*4+3], self.OAM[spr*4+1], self.OAM[spr*4+2]])
            spr += 1
        cdef int tile_y = (lineNum - self.bgscrolly) & 255
        cdef int tile_ty = tile_y >> 3
        cdef int tile_iy = tile_y & 7
        cdef int x = 0
        cdef int tile_x, tile_tx, tile_ix
        while x < 256:
            tile_x = (x - self.bgscrollx) & 255
            tile_tx = tile_x >> 3
            tile_ix = tile_x & 7
            tile_idx = vmem[nametable + tile_y * 32 + tile_x]
            color = vmem[0x3f00]
            linemap[x] = self.PALETTE[color]
            x += 1

class NESStandardTilemapCell:
    def __init__(self):
        self.tile = 0
        self.flipv = False
        self.fliph = False
