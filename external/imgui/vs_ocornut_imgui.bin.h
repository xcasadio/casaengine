static const uint8_t vs_ocornut_imgui_glsl[523] =
{
	0x56, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, 0x5f, 0x76, 0x69, 0x65, // VSH........u_vie
	0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0xea, 0x01, 0x00, 0x00, // wTexel..........
	0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // attribute highp 
	0x76, 0x65, 0x63, 0x34, 0x20, 0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x61, // vec4 a_color0;.a
	0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, // ttribute highp v
	0x65, 0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, // ec3 a_position;.
	0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // attribute highp 
	0x76, 0x65, 0x63, 0x32, 0x20, 0x61, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, // vec2 a_texcoord0
	0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // ;.varying highp 
	0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x76, // vec4 v_color0;.v
	0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, // arying highp vec
	0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, // 2 v_texcoord0;.u
	0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, // niform highp vec
	0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x3b, 0x0a, 0x76, // 4 u_viewTexel;.v
	0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, // oid main ().{.  
	0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // highp vec2 tmpva
	0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, // r_1;.  tmpvar_1 
	0x3d, 0x20, 0x28, 0x28, 0x32, 0x2e, 0x30, 0x20, 0x2a, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, // = ((2.0 * a_posi
	0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x78, 0x79, 0x29, 0x20, 0x2a, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, // tion.xy) * u_vie
	0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x2e, 0x78, 0x79, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x69, // wTexel.xy);.  hi
	0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // ghp vec4 tmpvar_
	0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x7a, 0x77, // 2;.  tmpvar_2.zw
	0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x32, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, //  = vec2(0.0, 1.0
	0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x78, 0x20, // );.  tmpvar_2.x 
	0x3d, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x20, 0x2d, 0x20, // = (tmpvar_1.x - 
	0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, // 1.0);.  tmpvar_2
	0x2e, 0x79, 0x20, 0x3d, 0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x74, 0x6d, 0x70, 0x76, // .y = (1.0 - tmpv
	0x61, 0x72, 0x5f, 0x31, 0x2e, 0x79, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, // ar_1.y);.  gl_Po
	0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // sition = tmpvar_
	0x32, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, // 2;.  v_texcoord0
	0x20, 0x3d, 0x20, 0x61, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, //  = a_texcoord0;.
	0x20, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x63, //   v_color0 = a_c
	0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                               // olor0;.}...
};
static const uint8_t vs_ocornut_imgui_dx9[367] =
{
	0x56, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, 0x5f, 0x76, 0x69, 0x65, // VSH........u_vie
	0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x50, 0x01, 0x00, 0x03, // wTexel......P...
	0xfe, 0xff, 0xfe, 0xff, 0x22, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x53, 0x00, // ....".CTAB....S.
	0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, // ................
	0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, // ..L...0.........
	0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, // ..<.......u_view
	0x54, 0x65, 0x78, 0x65, 0x6c, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, // Texel...........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, // ......vs_3_0.Mic
	0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, // rosoft (R) HLSL 
	0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, // Shader Compiler 
	0x39, 0x2e, 0x32, 0x39, 0x2e, 0x39, 0x35, 0x32, 0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x51, 0x00, // 9.29.952.3111.Q.
	0x00, 0x05, 0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0xbf, 0x00, 0x00, // .........@......
	0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, // .?..............
	0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0x90, 0x1f, 0x00, // ................
	0x00, 0x02, 0x05, 0x00, 0x00, 0x80, 0x02, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, // ................
	0x00, 0x80, 0x00, 0x00, 0x0f, 0xe0, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x01, 0x00, // ................
	0x0f, 0xe0, 0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x80, 0x02, 0x00, 0x03, 0xe0, 0x05, 0x00, // ................
	0x00, 0x03, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0xe4, 0x90, 0x04, 0x00, // ................
	0x00, 0x04, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xa0, 0x01, 0x00, // ................
	0x55, 0xa0, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0xe0, 0x00, 0x00, 0x55, 0x80, 0x01, 0x00, // U...........U...
	0x00, 0xa1, 0x01, 0x00, 0xaa, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0c, 0xe0, 0x01, 0x00, // ................
	0xb4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0xe4, 0x90, 0x01, 0x00, // ................
	0x00, 0x02, 0x02, 0x00, 0x03, 0xe0, 0x02, 0x00, 0xe4, 0x90, 0xff, 0xff, 0x00, 0x00, 0x00,       // ...............
};
static const uint8_t vs_ocornut_imgui_dx11[612] =
{
	0x56, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, 0x5f, 0x76, 0x69, 0x65, // VSH........u_vie
	0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x3c, 0x02, 0x44, 0x58, // wTexel......<.DX
	0x42, 0x43, 0x22, 0x5c, 0xcc, 0x36, 0x58, 0xb2, 0x23, 0x45, 0x8a, 0x2b, 0xbd, 0x13, 0xac, 0xf2, // BC"..6X.#E.+....
	0xa4, 0x09, 0x01, 0x00, 0x00, 0x00, 0x3c, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, // ......<.......,.
	0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x68, 0x00, // ..........ISGNh.
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, // ..........P.....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, // ................
	0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, // ..V.............
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, // .........._.....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x03, // ................
	0x00, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, // ..COLOR.POSITION
	0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0x6c, 0x00, // .TEXCOORD.OSGNl.
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, // ..........P.....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // ................
	0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, // ................
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, // ..........b.....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x0c, // ................
	0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x43, 0x4f, // ..SV_POSITION.CO
	0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0xab, 0x53, 0x48, // LOR.TEXCOORD..SH
	0x44, 0x52, 0x24, 0x01, 0x00, 0x00, 0x40, 0x00, 0x01, 0x00, 0x49, 0x00, 0x00, 0x00, 0x59, 0x00, // DR$...@...I...Y.
	0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5f, 0x00, // ..F. ........._.
	0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, 0x32, 0x10, // .........._...2.
	0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, 0x32, 0x10, 0x10, 0x00, 0x02, 0x00, // ......_...2.....
	0x00, 0x00, 0x67, 0x00, 0x00, 0x04, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // ..g.... ........
	0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, // ..e.... ......e.
	0x00, 0x03, 0x32, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, 0x01, 0x00, // ..2 ......h.....
	0x00, 0x00, 0x36, 0x00, 0x00, 0x08, 0xc2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, // ..6.... .......@
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x80, 0x3f, 0x38, 0x00, 0x00, 0x08, 0x32, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x10, // .?8...2.......F.
	0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ......F. .......
	0x00, 0x00, 0x32, 0x00, 0x00, 0x09, 0x12, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, // ..2.... ........
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x40, // .......@.....@.@
	0x00, 0x00, 0x00, 0x00, 0x80, 0xbf, 0x32, 0x00, 0x00, 0x0a, 0x22, 0x20, 0x10, 0x00, 0x00, 0x00, // ......2..." ....
	0x00, 0x00, 0x1a, 0x00, 0x10, 0x80, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, // ......A........@
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x36, 0x00, // .....@.@.....?6.
	0x00, 0x05, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x1e, 0x10, 0x00, 0x00, 0x00, // ... ......F.....
	0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x32, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x46, 0x10, // ..6...2 ......F.
	0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x03, 0x05, 0x00, 0x01, 0x00, // ......>.........
	0x10, 0x00, 0x10, 0x00,                                                                         // ....
};
