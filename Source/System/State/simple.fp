!!ARBfp1.0
TEMP tex0;
TEX tex0, fragment.texcoord, texture[0], 2D;
MUL result.color, tex0, fragment.color;
END
