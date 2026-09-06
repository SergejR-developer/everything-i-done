class Binary():
    def __init__(self, code: str): 
        self.code = code
        for bit in code:
            if (int(bit) != 0) and (int(bit) != 1): raise ValueError('Binary code contains only 0 and 1')

    def change(self, new_code: str) -> str:
        #Changes binary code to new_code
        self.code = new_code

    def convert(self) -> int:
        #Converts binary class into an integer in decimal system
        dec = 0
        for i, bit in enumerate(self.code):
            dec += int(bit)*2**(len(self.code)-i-1)
        return dec

code = Binary('1010')

code.change('10111010000')

decimal = code.convert()

print(decimal)