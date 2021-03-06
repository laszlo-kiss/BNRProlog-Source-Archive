/*
*
*  $Header: /disc9/sniff/repository/BNRProlog/source/RCS/interval.h,v 1.1 1995/09/22 11:24:54 harrisja Exp $
*
*  $Log: interval.h,v $
 * Revision 1.1  1995/09/22  11:24:54  harrisja
 * Initial version.
 *
*
*/

/*****************************************************************
;************          Interval  Primitives            
;************          Aug 13 92 Version of make_C_interval_engine
;************          Source: newest pseudocode
;************          93 10 14 at 11:51
;*****************************************************************/



interval_op(add)
         lowerbd((xl + yl),vl);
         if (vl GT zl)  goto a_MUZL;
         if (vl EQ zl)  goto a_Upper;
   a_BackLX:
         lowerbd((zl - yh),vl);
         if (vl LE xl)  goto a_BackLY;
   a_MUXL:
         xl = vl;
         xlchng();
   a_BackLY:
         lowerbd((zl - xh),vl);
         if (vl LE yl)  goto a_Upper;
   a_MUYL:
         yl = vl;
         ylchng();
         goto a_Upper;
   a_MUZL:
         zl = vl;
         zlchng();
   a_Upper:
         upperbd((xh + yh),vh);
         if (vh LT zh)  goto a_MUZH;
         if (vh EQ zh)  goto a_Exit;
   a_BackHX:
         upperbd((zh - yl),vh);
         if (vh GE xh)  goto a_BackHY;
   a_MUXH:
         xh = vh;
         xhchng();
   a_BackHY:
         upperbd((zh - xl),vh);
         if (vh GE yh)  goto a_Exit;
   a_MUYH:
         yh = vh;
         yhchng();
         goto a_Exit;
   a_MUZH:
         zh = vh;
         zhchng();
   a_Exit:
         success();
end_op(add)



interval_op(begin_tog)
         if (xl GT zl)  goto b_Chkzl;
         if (xl EQ zl)  goto b_Exit;
   b_Chkxl:
         xl = zl;
         xlchng();
         goto b_Exit;
   b_Chkzl:
         zl = xl;
         zlchng();
   b_Exit:
         success();
end_op(begin_tog)



interval_op(cos)
         if (xl GE 0)  goto c_Right;
   c_Mleft:
         if (xh GT 0)  goto c_Center;
   c_Left:
         swap(x);
   c_Right:
         upperbd2(cos(xl),uh);
         if (uh GT zh)  goto c_Uxl;
         if (uh EQ zh)  goto c_Low;
   c_Uzh:
         zh = uh;
         zhchng();
         goto c_Low;
   c_Uxl:
         lowerbd2(acos(zh),vl);
         if (vl LE xl)  goto c_Low;
   c_Uxl2:
         xl = vl;
         xlchng();
   c_Low:
         lowerbd2(cos(xh),ul);
         if (ul LT zl)  goto c_Uxh;
         if (ul EQ zl)  goto c_Exit;
   c_Uzl:
         zl = ul;
         zlchng();
         goto c_Exit;
   c_Uxh:
         upperbd2(acos(zl),vh);
         if (vh GE xh)  goto c_Exit;
   c_Uxh2:
         xh = vh;
         xhchng();
         goto c_Exit;
   c_Center:
         ul = (- xl);
         if (xh GE ul)  goto c_Hright;
   c_Hleft:
         swap(x);
   c_Hright:
         lowerbd2(cos(xl),ul);
         upperbd2(cos(xh),uh);
         vl = 1;
         if (zh LT uh)  goto c_Fail;
   c_Meets:
         if (zh GE ul)  goto c_Chklo;
   c_Unxl:
         lowerbd2(acos(zh),vl);
         if (vl LE xl)  goto c_Chklo;
   c_Unxl2:
         xl = vl;
         xlchng();
   c_Chklo:
         if (zl GT uh)  goto c_Uxh;
         if (zl EQ uh)  goto c_Exit;
   c_Upzl:
         zl = uh;
         zlchng();
         goto c_Exit;
   c_Fail:
         fail();
   c_Exit:
         success();
end_op(cos)


interval_op(equal)
         if (xl GT zl)  goto e_Chkzl;
         if (xl EQ zl)  goto e_Ub;
   e_Chkxl:
         xl = zl;
         xlchng();
         goto e_Ub;
   e_Chkzl:
         zl = xl;
         zlchng();
   e_Ub:
         if (xh GT zh)  goto e_Chkxh;
         if (xh EQ zh)  goto e_Exit;
   e_Chkzh:
         zh = xh;
         zhchng();
         goto e_Exit;
   e_Chkxh:
         xh = zh;
         xhchng();
   e_Exit:
         success();
end_op(equal)



interval_op(finish_tog)
         if (xh GT zh)  goto f_Chkxh;
         if (xh EQ zh)  goto f_Exit;
   f_Chkzh:
         zh = xh;
         zhchng();
         goto f_Exit;
   f_Chkxh:
         xh = zh;
         xhchng();
   f_Exit:
         success();
end_op(finish_tog)



interval_op(greatereq)
         if (xh LT zl)  goto g_Done;
   g_Lb:
         if (xl LE zl)  goto g_Ub;
   g_Chkzl:
         zl = xl;
         zlchng();
   g_Ub:
         if (xh LE zh)  goto g_Exit;
   g_Chkxh:
         xh = zh;
         xhchng();
         goto g_Exit;
   g_Done:
         deact();
   g_Exit:
         success();
end_op(greatereq)



interval_op(higher)
         if (zh LT xl)  goto h_Done;
   h_Lb:
         if (zl LT xl)  goto h_Ub;
   h_Chkxl:
         xl = zl;
         next(xl);
         xlchng();
   h_Ub:
         if (zh LT xh)  goto h_Exit;
   h_Chkzh:
         zh = xh;
         prev(zh);
         zhchng();
         goto h_Exit;
   h_Done:
         deact();
   h_Exit:
         success();
end_op(higher)



interval_op(inf)
         if (zl LE xl)  goto i_Ubzx;
   i_Chkxl:
         xl = zl;
         xlchng();
   i_Ubzx:
         if (zh LE xh)  goto i_LtY;
   i_Chkxh:
         zh = xh;
         zhchng();
   i_LtY:
         if (zl LE yl)  goto i_Ubzy;
   i_Chkyl:
         yl = zl;
         ylchng();
   i_Ubzy:
         if (zh LE yh)  goto i_Ubx;
   i_Chkyh:
         zh = yh;
         zhchng();
   i_Ubx:
         if (zh GE yl)  goto i_Uby;
   i_Uxh1:
         if (zh GE xh)  goto i_LbZ;
   i_Uxh:
         xh = zh;
         xhchng();
         goto i_LbZ;
   i_Uby:
         if (zh GE xl)  goto i_LbZ;
   i_Uyh1:
         if (zh GE yh)  goto i_LbZ;
   i_Uyh:
         yh = zh;
         yhchng();
   i_LbZ:
         if (xl GT yl)  goto i_Usey;
   i_Usex:
         vl = xl;
         goto i_Chkzl;
   i_Usey:
         vl = yl;
   i_Chkzl:
         if (vl LE zl)  goto i_Exit;
   i_Chkzh:
         zl = vl;
         zlchng();
   i_Exit:
         success();
end_op(inf)



interval_op(j_less)
         if (yl GT 0)  goto greatereq;
         if (yl LT 0)  iaerror();
   j_Mfalse:
         if (yh LT 0)  iaerror();
         if (yh EQ 0)  goto higher;
   j_Test:
         if (xh LE zl)  goto j_True;
   j_Test2:
         if (zh LT xl)  goto j_False;
         goto j_Exit;
   j_True:
         yl = 1;
         ylchng();
         goto j_Exit;
   j_False:
         yh = 0;
         yhchng();
   j_Exit:
         success();
end_op(j_less)



interval_op(k_equal)
         if (yl GT 0)  goto equal;
         if (yl LT 0)  iaerror();
   k_Mfalse:
         if (yh LT 0)  iaerror();
         if (yh EQ 0)  goto unequal;
   k_Test:
         if (zl GT xh)  goto k_Un;
         if (zl EQ xh)  goto k_Tryeq;
   k_Test2:
         if (xl LE zh)  goto k_Exit;
   k_Un:
         yh = 0;
         yhchng();
         goto k_Exit;
   k_Tryeq:
         if (zl NE zh)  goto k_Exit;
   k_Tryeq2:
         if (xl NE xh)  goto k_Exit;
   k_Eq:
         yl = 1;
         ylchng();
   k_Exit:
         success();
end_op(k_equal)



interval_op(lub)
         if (xl LE zl)  goto l_Ubx;
   l_Chkxl:
         zl = xl;
         zlchng();
   l_Ubx:
         if (xh LE zh)  goto l_LtY;
   l_Chkxh:
         xh = zh;
         xhchng();
   l_LtY:
         if (yl LE zl)  goto l_Uby;
   l_Chkyl:
         zl = yl;
         zlchng();
   l_Uby:
         if (yh LE zh)  goto l_Lbx;
   l_Chkyh:
         yh = zh;
         yhchng();
   l_Lbx:
         if (zl LE xh)  goto l_Lby;
   l_Uyl1:
         if (zl LE yl)  goto l_UbZ;
   l_Uyl:
         yl = zl;
         ylchng();
         goto l_UbZ;
   l_Lby:
         if (zl LE yh)  goto l_UbZ;
   l_Uxl1:
         if (zl LE xl)  goto l_UbZ;
   l_Uxl:
         xl = zl;
         xlchng();
   l_UbZ:
         if (yh GT xh)  goto l_Usey;
   l_Usex:
         vh = xh;
         goto l_Chkzh;
   l_Usey:
         vh = yh;
   l_Chkzh:
         if (vh GE zh)  goto l_Exit;
   l_Chkzl:
         zh = vh;
         zhchng();
   l_Exit:
         success();
end_op(lub)



interval_op(mul)
         if (xl GT 0)  goto m_Xpos;
         if (xl EQ 0)  goto m_XMpos;
   m_Chkxh:
         if (xh GT 0)  goto m_Xindef;
   m_Swx:
         swap(x);
   m_Xneg:
         if (yl GT 0)  goto m_Zneg;
         if (yl EQ 0)  goto m_ZMneg;
   m_Chkyh1:
         if (yh GT 0)  goto m_Yindef1;
   m_Swy1:
         swap(y);
         goto m_Zpos;
   m_Yindef1:
         if (zl GE 0)  goto m_MakeYneg;
   m_Chkzh1:
         if (zh GT 0)  goto m_FZ;
   m_Swz1:
         swap(z);
         goto m_MakeYpos;
   m_FZ:
         swap(z);
         goto m_MpyBX;
   m_ZMneg:
         if (yh LT 0)  goto m_Fail;
         if (yh GT 0)  goto m_Zneg;
         goto m_ZZero;
   m_Xindef:
         if (yl GT 0)  goto m_Ypos;
         if (yl EQ 0)  goto m_YMpos;
   m_Chkyh2:
         if (yh GT 0)  goto m_MpyC;
   m_Yneg:
         swap(y);
         if (zl GE 0)  goto m_MakeXneg;
   m_Chzh2:
         if (zh GT 0)  goto m_FZ2;
   m_Swz2:
         swap(z);
         goto m_MakeXpos;
   m_FZ2:
         swap(z);
         goto m_MpyBY;
   m_YMpos:
         if (yh LT 0)  goto m_Fail;
         if (yh EQ 0)  goto m_ZZero;
   m_Ypos:
         if (zl GE 0)  goto m_MakeXpos;
   m_Chzh3:
         if (zh GT 0)  goto m_MpyBY;
   m_Swz3:
         swap(z);
         goto m_MakeXneg;
   m_XMpos:
         if (xh LT 0)  goto m_Fail;
         if (xh EQ 0)  goto m_ZZero;
   m_Xpos:
         if (yl GT 0)  goto m_Zpos;
         if (yl EQ 0)  goto m_ZMpos;
   m_Chkyh:
         if (yh GT 0)  goto m_Yindef;
   m_Swy:
         swap(y);
         goto m_Zneg;
   m_Yindef:
         if (zl GE 0)  goto m_MakeYpos;
   m_Chkzh:
         if (zh GT 0)  goto m_MpyBX;
   m_Swz4:
         swap(z);
         goto m_MakeYneg;
   m_ZMpos:
         if (yh LT 0)  goto m_Fail;
         if (yh GT 0)  goto m_Zpos;
         goto m_ZZero;
   m_MpyC:
         lowerbd((xl * yh),vh);
         lowerbd((xh * yl),vl);
         if (vh LE vl)  goto m_Usevh;
   m_Usevl:
         vh = vl;
   m_Usevh:
         if (vh LE zl)  goto m_MpyCH;
   m_Uzlvh:
         zl = vh;
         zlchng();
   m_MpyCH:
         upperbd((xl * yl),vl);
         upperbd((xh * yh),vh);
         if (vl GE vh)  goto m_Usevl2;
   m_Usevh2:
         vl = vh;
   m_Usevl2:
         if (vl GE zh)  goto m_Exit;
   m_Uzhvl:
         zh = vl;
         zhchng();
         goto m_Exit;
   m_MpyBX:
         lowerbd((xh * yl),vl);
         if (vl LT zl)  goto m_Backxzl;
         if (vl EQ zl)  goto m_MpyBHX;
   m_Uzl1:
         zl = vl;
         zlchng();
         goto m_MpyBHX;
   m_Backxzl:
         if (xl LE 0)  goto m_MpyBHX;
   m_BXDivl:
         lowerbd((zl / xl),vl);
         if (vl LE yl)  goto m_MpyBHX;
   m_Uyl1:
         yl = vl;
         ylchng();
   m_MpyBHX:
         upperbd((xh * yh),vh);
         if (vh LT zh)  goto m_MUZH;
         if (vh EQ zh)  goto m_Exit;
   m_Backxzh:
         if (xl LE 0)  goto m_Exit;
   m_BXDivh:
         upperbd((zh / xl),vh);
         if (vh LT yh)  goto m_MUYH;
         goto m_Exit;
   m_MpyBY:
         lowerbd((yh * xl),vl);
         if (vl LT zl)  goto m_Backyzl;
         if (vl EQ zl)  goto m_MpyBHY;
   m_Uzl2:
         zl = vl;
         zlchng();
         goto m_MpyBHY;
   m_Backyzl:
         if (yl LE 0)  goto m_MpyBHY;
   m_BYDivl:
         lowerbd((zl / yl),vl);
         if (vl LE xl)  goto m_MpyBHY;
   m_Uyl2:
         xl = vl;
         xlchng();
   m_MpyBHY:
         upperbd((xh * yh),vh);
         if (vh LT zh)  goto m_MUZH;
         if (vh EQ zh)  goto m_Exit;
   m_Backyzh:
         if (yl LE 0)  goto m_Exit;
   m_BYDivh:
         upperbd((zh / yl),vh);
         if (vh LT xh)  goto m_MUXH;
         goto m_Exit;
   m_ZZero:
         if (zl GT 0)  goto m_Fail;
         if (zl EQ 0)  goto m_Zh;
   m_Zl_0:
         zl = 0;
         zlchng();
   m_Zh:
         if (zh LT 0)  goto m_Fail;
         if (zh EQ 0)  goto m_Exit;
   m_Zh_0:
         zh = 0;
         zhchng();
         goto m_Exit;
   m_MakeXneg:
         swap(x);
   m_MakeXpos:
         xl = 0;
         xlchng();
         goto m_MpyA;
   m_MakeYneg:
         swap(y);
   m_MakeYpos:
         yl = 0;
         ylchng();
         goto m_MpyA;
   m_Zneg:
         if (zh LE 0)  goto m_Swz;
   m_Chzl:
         swap(z);
         zl = 0;
         zlchng();
         goto m_MpyA;
   m_Swz:
         swap(z);
         goto m_MpyA;
   m_Zpos:
         if (zl GE 0)  goto m_MpyA;
   m_Chzh:
         zl = 0;
         zlchng();
   m_MpyA:
         lowerbd((xl * yl),vl);
         if (vl GT zl)  goto m_MUZL;
         if (vl EQ zl)  goto m_Upper;
   m_BackLX:
         if (yh LE 0)  goto m_BackLY;
   m_DivL:
         lowerbd((zl / yh),vl);
         if (vl LE xl)  goto m_BackLY;
   m_MUXL:
         xl = vl;
         xlchng();
   m_BackLY:
         if (xh LE 0)  goto m_Upper;
   m_BLY:
         lowerbd((zl / xh),vl);
         if (vl LE yl)  goto m_Upper;
   m_MUYL:
         yl = vl;
         ylchng();
         goto m_Upper;
   m_MUZL:
         zl = vl;
         zlchng();
   m_Upper:
         upperbd((xh * yh),vh);
         if (vh LT zh)  goto m_MUZH;
         if (vh EQ zh)  goto m_Exit;
   m_BackHX:
         if (yl LE 0)  goto m_BackHY;
   m_DivH:
         upperbd((zh / yl),vh);
         if (vh GE xh)  goto m_BackHY;
   m_MUXH:
         xh = vh;
         xhchng();
   m_BackHY:
         if (xl LE 0)  goto m_Exit;
   m_BHY:
         upperbd((zh / xl),vh);
         if (vh GE yh)  goto m_Exit;
   m_MUYH:
         yh = vh;
         yhchng();
         goto m_Exit;
   m_MUZH:
         zh = vh;
         zhchng();
   m_Exit:
         success();
   m_Fail:
         fail();
end_op(mul)



interval_op(narrower)
         if (xl GE zl)  goto n_Ub;
   n_Chkxl:
         xl = zl;
         xlchng();
   n_Ub:
         if (xh LE zh)  goto n_Exit;
   n_Chkxh:
         xh = zh;
         xhchng();
   n_Exit:
         success();
end_op(narrower)



interval_op(or)
         if (xl GT yl)  goto o_YX;
   o_XY:
         if (zl GT xl)  goto o_DisjX;
         if (zl EQ xl)  goto o_DX3;
   o_Uzlxl:
         zl = xl;
         zlchng();
         goto o_DX3;
   o_DisjX:
         if (xh LT zl)  goto o_EqZY;
   o_DX2:
         if (yh LT zl)  goto o_EqZX;
   o_DX3:
         if (zh LT yl)  goto o_EqZX;
         goto o_PartB;
   o_YX:
         if (zl GT yl)  goto o_DisjY;
         if (zl EQ yl)  goto o_DY3;
   o_Uzlyl:
         zl = yl;
         zlchng();
         goto o_DY3;
   o_DisjY:
         if (yh LT zl)  goto o_EqZX;
   o_DY2:
         if (xh LT zl)  goto o_EqZY;
   o_DY3:
         if (zh GE xl)  goto o_PartB;
   o_EqZY:
         if (zl GT yl)  goto o_Uyzl;
         if (zl EQ yl)  goto o_HYZ;
   o_Uzyl:
         zl = yl;
         zlchng();
         goto o_HYZ;
   o_Uyzl:
         yl = zl;
         ylchng();
   o_HYZ:
         if (zh LT yh)  goto o_Uyzh;
         if (zh GT yh)  goto o_Uzyh;
         goto o_Exit;
   o_EqZX:
         if (zl GT xl)  goto o_Uxzl;
         if (zl EQ xl)  goto o_HXZ;
   o_Uzxl:
         zl = xl;
         zlchng();
         goto o_HXZ;
   o_Uxzl:
         xl = zl;
         xlchng();
   o_HXZ:
         if (zh LT xh)  goto o_Uxzh;
         if (zh GT xh)  goto o_Uzxh;
         goto o_Exit;
   o_PartB:
         if (xh GE yh)  goto o_UBX;
   o_UBY:
         if (zh LE yh)  goto o_Exit;
   o_Uzyh:
         zh = yh;
         zhchng();
         goto o_Exit;
   o_UBX:
         if (zh LE xh)  goto o_Exit;
   o_Uzxh:
         zh = xh;
         zhchng();
         goto o_Exit;
   o_Uyzh:
         yh = zh;
         yhchng();
         goto o_Exit;
   o_Uxzh:
         xh = zh;
         xhchng();
   o_Exit:
         success();
   o_Fail:
         fail();
end_op(or)



interval_op(pow_odd)
         if (zl GE 0)  goto p_Right;
   p_Chkub:
         if (zh LE 0)  goto p_Left;
   p_MayCenter:
         if (xl GE 0)  goto p_Rightx;
   p_Chubx:
         if (xh LE 0)  goto p_Leftx;
   p_Center:
         vl = (- zl);
         upperbd2(ln(vl),vl);
         upperbd((vl / yl),vl);
         upperbd2(exp(vl),vl);
         vl = (- vl);
         if (vl GT xl)  goto p_Uxl;
         if (vl EQ xl)  goto p_Ub;
   p_CUzl:
         if (xl GT 0)  goto p_Uzl;
         if (xl EQ 0)  goto p_Zxl;
   p_Negxl:
         vl = (- xl);
         upperbd2(ln(vl),vl);
         upperbd((vl * yl),vl);
         upperbd2(exp(vl),vl);
         vl = (- vl);
         goto p_UzlC;
   p_Zxl:
         zl = 0;
         zlchng();
         goto p_Ub;
   p_Leftx:
         swap(z);
         swap(x);
   p_Rightx:
         zl = 0;
         zlchng();
         goto p_Right;
   p_Left:
         swap(z);
         swap(x);
   p_Right:
         if (zl GT 0)  goto p_NZl;
   p_Zl:
         vl = 0;
         goto p_Lbch;
   p_NZl:
         lowerbd2(ln(zl),vl);
         lowerbd((vl / yl),vl);
         lowerbd2(exp(vl),vl);
   p_Lbch:
         if (vl LT xl)  goto p_Uzl;
         if (vl EQ xl)  goto p_Ub;
   p_Uxl:
         xl = vl;
         xlchng();
         goto p_Ub;
   p_Uzl:
         lowerbd2(ln(xl),vl);
         lowerbd((vl * yl),vl);
         lowerbd2(exp(vl),vl);
   p_UzlC:
         if (vl LE zl)  goto p_Ub;
   p_Upzl:
         zl = vl;
         zlchng();
   p_Ub:
         if (zh GT 0)  goto p_NZh;
   p_Zh:
         vh = 0;
         goto p_Ubch;
   p_NZh:
         upperbd2(ln(zh),vh);
         upperbd((vh / yl),vh);
         upperbd2(exp(vh),vh);
   p_Ubch:
         if (vh GT xh)  goto p_Uzh;
         if (vh EQ xh)  goto p_Exit;
   p_Uxh:
         xh = vh;
         xhchng();
         goto p_Exit;
   p_Uzh:
         if (xh GT 0)  goto p_Uzhp;
         if (xh EQ 0)  goto p_Uzhz;
   p_Uzhn:
         vh = (- xh);
         lowerbd2(ln(vh),vh);
         lowerbd((vh * yl),vh);
         lowerbd2(exp(vh),vh);
         vh = (- vh);
         goto p_UzhC;
   p_Uzhz:
         zh = 0;
         zhchng();
         goto p_Exit;
   p_Uzhp:
         upperbd2(ln(xh),vh);
         upperbd((vh * yl),vh);
         upperbd2(exp(vh),vh);
   p_UzhC:
         if (vh GE zh)  goto p_Exit;
   p_Upzh:
         zh = vh;
         zhchng();
   p_Exit:
         success();
end_op(pow_odd)



interval_op(qpow_even)
         if (zl GT 0)  goto q_Nonz;
         if (zl EQ 0)  goto q_Zero;
   q_SZ:
         if (zh LT 0)  goto q_Fail;
   q_SZ1:
         zl = 0;
         zlchng();
   q_Zero:
         vl = 0;
         if (zh GT 0)  goto q_Dovh;
   q_Zvh:
         vh = 0;
   q_ZChkXl:
         if (xl GT 0)  goto q_Fail;
         if (xl EQ 0)  goto q_ZChkXh;
   q_Zxl:
         xl = 0;
         xlchng();
   q_ZChkXh:
         if (xh LT 0)  goto q_Fail;
         if (xh EQ 0)  goto q_Exit;
   q_Zxh:
         xh = 0;
         xhchng();
         goto q_Exit;
   q_Nonz:
         lowerbd2(ln(zl),vl);
         lowerbd((vl / yl),vl);
         lowerbd2(exp(vl),vl);
   q_Dovh:
         upperbd2(ln(zh),vh);
         upperbd((vh / yl),vh);
         upperbd2(exp(vh),vh);
   q_ChkX:
         if (xl GE 0)  goto q_Eq;
   q_Chkub:
         if (xh LE 0)  goto q_Flp;
   q_Sp0:
         uh = (- xl);
         if (uh LT vl)  goto q_Eq;
   q_Mayleft:
         if (xh LT vl)  goto q_Flp;
   q_Both:
         if (uh GT xh)  goto q_Lefthi;
   q_Righthi:
         uh = xh;
   q_Lefthi:
         if (uh GT vh)  goto q_Trimxl;
         if (uh EQ vh)  goto q_Exit;
   q_Trimvh:
         vh = uh;
         goto q_Uzhvh;
   q_Trimxl:
         uh = (- xl);
         if (uh LE vh)  goto q_Trimxh;
   q_Trim_low:
         xl = (- vh);
         xlchng();
   q_Trimxh:
         if (xh LE vh)  goto q_Exit;
         goto q_Uxh;
   q_Flp:
         uh = vh;
         swap(x);
         vh = uh;
   q_Eq:
         if (vl LT xl)  goto q_Uzl;
         if (vl EQ xl)  goto q_Ub;
   q_Uxl:
         xl = vl;
         xlchng();
         goto q_Ub;
   q_Uzl:
         lowerbd2(ln(xl),vl);
         lowerbd((vl * yl),vl);
         lowerbd2(exp(vl),vl);
         if (vl LE zl)  goto q_Ub;
   q_Upzl:
         zl = vl;
         zlchng();
   q_Ub:
         if (vh GT xh)  goto q_Uzh;
         if (vh EQ xh)  goto q_Exit;
   q_Uxh:
         xh = vh;
         xhchng();
         goto q_Exit;
   q_Uzh:
         vh = xh;
   q_Uzhvh:
         upperbd2(ln(vh),vh);
         upperbd((vh * yl),vh);
         upperbd2(exp(vh),vh);
         if (vh GE zh)  goto q_Exit;
   q_Upzh:
         zh = vh;
         zhchng();
         goto q_Exit;
   q_Fail:
         fail();
   q_Exit:
         success();
end_op(qpow_even)



interval_op(rootsquare)
         if (xl GE 0)  goto r_Eq;
   r_Chkub:
         if (xh LE 0)  goto r_Flp;
   r_Sp0:
         upperbd((xl * xl),ul);
         if (ul LT zl)  goto r_Zeroxl;
   r_Tryxh:
         upperbd((xh * xh),uh);
         if (uh LT zl)  goto r_Zeroxh;
   r_Zlb:
         if (zl GE 0)  goto r_Zub;
   r_MUzl:
         zl = 0;
         zlchng();
   r_Zub:
         if (ul GT uh)  goto r_Zhul;
   r_Zhxh:
         if (uh GT zh)  goto r_Mxh;
         if (uh EQ zh)  goto r_Exit;
   r_Mzhxh:
         zh = uh;
         zhchng();
         goto r_Exit;
   r_Mxh:
         upperbd(sqrt(zh),uh);
         if (uh GE xh)  goto r_Exit;
   r_Uxh:
         xh = uh;
         xhchng();
         uh = (- uh);
         if (uh LE xl)  goto r_Exit;
   r_Uh:
         xl = uh;
         xlchng();
         goto r_Exit;
   r_Zhul:
         if (ul GT zh)  goto r_Mxh2;
         if (ul EQ zh)  goto r_Exit;
   r_Mzhuh:
         zh = ul;
         zhchng();
         goto r_Exit;
   r_Mxh2:
         upperbd(sqrt(zh),uh);
         uh = (- uh);
         if (uh LE xl)  goto r_Exit;
   r_Uxl:
         xl = uh;
         xlchng();
         uh = (- uh);
         if (uh GE xh)  goto r_Exit;
   r_Uh2:
         xh = uh;
         xhchng();
         goto r_Exit;
   r_Flp:
         swap(x);
         goto r_Eq;
   r_Zeroxh:
         swap(x);
   r_Zeroxl:
         xl = 0;
         xlchng();
   r_Eq:
         lowerbd((xl * xl),ul);
         upperbd((xh * xh),uh);
         if (ul GT zl)  goto r_Chkzl;
         if (ul EQ zl)  goto r_Ub;
   r_Chkxl:
         lowerbd(sqrt(zl),ul);
         if (ul LE xl)  goto r_Ub;
   r_Upxl:
         xl = ul;
         xlchng();
         goto r_Ub;
   r_Chkzl:
         zl = ul;
         zlchng();
   r_Ub:
         if (uh GT zh)  goto r_Chkxh;
         if (uh EQ zh)  goto r_Exit;
   r_Chkzh:
         zh = uh;
         zhchng();
         goto r_Exit;
   r_Chkxh:
         upperbd(sqrt(zh),uh);
         if (uh GE xh)  goto r_Exit;
   r_Upxh:
         xh = uh;
         xhchng();
   r_Exit:
         success();
end_op(rootsquare)



interval_op(sin)
         vl = 2;
         vh = pi();
         vh = (vh / vl);
         vl = (- vh);
         if (xh GT vh)  goto s_MRight;
   s_Mcenter:
         if (xl LT vl)  goto s_MLeft;
   s_Center:
         upperbd2(sin(xh),uh);
         lowerbd2(sin(xl),ul);
         if (zh GT uh)  goto s_Uzh;
         if (zh EQ uh)  goto s_Low;
   s_Uxh:
         upperbd2(asin(zh),uh);
         if (uh GE xh)  goto s_Low;
   s_Uxh2:
         xh = uh;
         xhchng();
         goto s_Low;
   s_Uzh:
         zh = uh;
         zhchng();
   s_Low:
         if (zl LT ul)  goto s_Uzl;
         if (zl GT ul)  goto s_Uxl;
         goto s_Exit;
   s_MLeft:
         swap(x);
         swap(z);
         vh = (- vl);
   s_MRight:
         if (xl LT 0)  goto s_ForceR;
   s_Pos:
         if (xl LT vh)  goto s_CR;
         goto s_Right;
   s_ForceR:
         if (zl GE 0)  goto s_CR;
   s_Leftbranch:
         if (xl LT vl)  goto s_Exit;
         goto s_CR;   /* 10 May 95 W.J.O.  */
   s_Right:
         upperbd2(sin(xl),ul);
         lowerbd2(sin(xh),uh);
         if (ul GT zh)  goto s_Urxl;
         if (ul EQ zh)  goto s_Rlow;
   s_Urzh:
         zh = ul;
         zhchng();
         goto s_Rlow;
   s_Urxl:
         lowerbd2(acos(zh),vl);
         lowerbd((vl + vh),vl);
         if (vl LE xl)  goto s_Rlow;
   s_Urxl2:
         xl = vl;
         xlchng();
   s_Rlow:
         if (uh LT zl)  goto s_Urxh;
         if (uh EQ zl)  goto s_Exit;
   s_Uzh2:
         zl = uh;
         zlchng();
         goto s_Exit;
   s_Urxh:
         upperbd2(acos(zl),vl);
         upperbd((vl + vh),vh);
         if (vh GE xh)  goto s_Exit;
   s_Urxh2:
         xh = vh;
         xhchng();
         goto s_Exit;
   s_CR:
         lowerbd2(sin(xl),ul);
         lowerbd2(sin(xh),uh);
         if (ul GT uh)  goto s_CRR;
   s_CRL:
         if (zh LT uh)  goto s_Uxh;
         goto s_Low;
   s_CRR:
         if (zh LT ul)  goto s_Urxl;
         goto s_Rlow;
   s_Uxl:
         lowerbd2(asin(zl),vl);
         if (vl LE xl)  goto s_Exit;
   s_Uxl2:
         xl = vl;
         xlchng();
         goto s_Exit;
   s_Uzl:
         zl = ul;
         zlchng();
   s_Exit:
         success();
end_op(sin)



interval_op(tan)
         lowerbd2(tan(xl),ul);
         upperbd2(tan(xh),uh);
         if (ul LT zl)  goto t_BackL;
         if (ul EQ zl)  goto t_NonsingH;
   t_Uzl:
         zl = ul;
         zlchng();
         goto t_NonsingH;
   t_BackL:
         lowerbd2(atan(zl),ul);
         if (ul LE xl)  goto t_NonsingH;
   t_Uxl:
         xl = ul;
         xlchng();
   t_NonsingH:
         if (uh GT zh)  goto t_BackH;
         if (uh EQ zh)  goto t_Exit;
   t_Chkzl:
         zh = uh;
         zhchng();
         goto t_Exit;
   t_BackH:
         upperbd2(atan(zh),uh);
         if (uh GE xh)  goto t_Exit;
   t_Uxh:
         xh = uh;
         xhchng();
   t_Exit:
         success();
end_op(tan)



interval_op(unequal)
         if (zh GT xl)  goto u_B;
         if (zh LT xl)  goto u_Done;
   u_Eq1:
         if (zl GT zh)  goto u_Fail;
         if (zl LT zh)  goto u_Eq12;
   u_XR:
         xl = xl;
         next(xl);
         xlchng();
         goto u_Done;
   u_Eq12:
         if (xl GT xh)  goto u_Fail;
         if (xl LT xh)  goto u_Exit;
   u_ZL:
         zh = zh;
         prev(zh);
         zhchng();
         goto u_Done;
   u_B:
         if (xh GT zl)  goto u_Exit;
         if (xh LT zl)  goto u_Done;
   u_Eq2:
         if (zl GT zh)  goto u_Fail;
         if (zl LT zh)  goto u_Eq22;
   u_XL:
         xh = xh;
         prev(xh);
         xhchng();
         goto u_Done;
   u_Eq22:
         if (xl GT xh)  goto u_Fail;
         if (xl LT xh)  goto u_Exit;
   u_ZR:
         zl = zl;
         next(zl);
         zlchng();
         goto u_Done;
   u_Fail:
         fail();
         goto u_Exit;
   u_Done:
         deact();
   u_Exit:
         success();
end_op(unequal)



interval_op(vabs)
         if (xl GE 0)  goto v_Eq;
   v_Chkub:
         if (xh LE 0)  goto v_Flp;
   v_Sp0:
         ul = (- xl);
         if (ul LT zl)  goto v_Zeroxl;
   v_Tryxh:
         if (xh LT zl)  goto v_Zeroxh;
   v_Zlb:
         if (zl GE 0)  goto v_Zub;
   v_MUzl:
         zl = 0;
         zlchng();
   v_Zub:
         if (ul GT xh)  goto v_Zhul;
   v_Zhxh:
         if (xh GT zh)  goto v_Mxh;
         if (xh EQ zh)  goto v_Exit;
   v_Mzhxh:
         zh = xh;
         zhchng();
         goto v_Exit;
   v_Zhul:
         if (ul GT zh)  goto v_Muh;
         if (ul EQ zh)  goto v_Exit;
   v_Mzhuh:
         zh = ul;
         zhchng();
         goto v_Exit;
   v_Muh:
         xl = (- zh);
         xlchng();
         if (xh LE zh)  goto v_Exit;
         goto v_Chkxh;
   v_Mxh:
         xh = zh;
         xhchng();
         if (ul LE zh)  goto v_Exit;
   v_Ul:
         xl = (- zh);
         xlchng();
         goto v_Exit;
   v_Zeroxl:
         xl = 0;
         xlchng();
         goto v_Eq;
   v_Zeroxh:
         xh = 0;
         xhchng();
   v_Flp:
         swap(x);
   v_Eq:
         if (xl GT zl)  goto v_Chkzl;
         if (xl EQ zl)  goto v_Ub;
   v_Chkxl:
         xl = zl;
         xlchng();
         goto v_Ub;
   v_Chkzl:
         zl = xl;
         zlchng();
   v_Ub:
         if (xh GT zh)  goto v_Chkxh;
         if (xh EQ zh)  goto v_Exit;
   v_Chkzh:
         zh = xh;
         zhchng();
         goto v_Exit;
   v_Chkxh:
         xh = zh;
         xhchng();
   v_Exit:
         success();
end_op(vabs)



interval_op(xp)
         if (zl GT 0)  goto x_Loglo;
         if (zl EQ 0)  goto x_Zeroch;
   x_Trim:
         zl = 0;
         zlchng();
   x_Zeroch:
         if (zh LE 0)  goto x_Fail;
         goto x_Expl;
   x_Loglo:
         lowerbd2(ln(zl),ul);
         if (xl GT ul)  goto x_Expl;
         if (xl EQ ul)  goto x_Loghi;
   x_Uxl:
         xl = ul;
         xlchng();
         goto x_Loghi;
   x_Expl:
         lowerbd2(exp(xl),ul);
         if (ul LE zl)  goto x_Loghi;
   x_Uzl:
         zl = ul;
         zlchng();
   x_Loghi:
         upperbd2(ln(zh),uh);
         if (uh GT xh)  goto x_Exph;
         if (uh EQ xh)  goto x_Exit;
   x_Uxh:
         xh = uh;
         xhchng();
         goto x_Exit;
   x_Exph:
         upperbd2(exp(xh),uh);
         if (uh GE zh)  goto x_Exit;
   x_Uzh:
         zh = uh;
         zhchng();
         goto x_Exit;
   x_Fail:
         fail();
   x_Exit:
         success();
end_op(xp)

interval_op(wrap)
         ul = 2;
         ul = (ul * yh);
         lowerbd((xl / ul),vl);
         roundnearest(vl);
         lowerbd((xh / ul),vh);
         roundnearest(vh);
         if (vl GT vh)  goto w_Exit;  
         if (vl EQ vh)  goto w_Same;
   w_Dif:
         ul = (- yh);
         if (zl GE ul)  goto w_Dif2;
   w_Uzl2:
         zl = ul;
         zlchng();
   w_Dif2:
         if (zh LE yh)  goto w_Exit;
   w_Uzh2:
         zh = yh;
         zhchng();
         goto w_Exit;
   w_Same:
         ul = (ul * vl);
         upperbd((xh - ul),vh);
         lowerbd((xl - ul),vl);
         if (zh GT vh)  goto w_Uzh;
         if (zh EQ vh)  goto w_Same2;
   w_MUxh:
         upperbd((zh + ul),vh);
         if (xh LE vh)  goto w_Same2;
   w_Uxh:
         xh = vh;
         xhchng();
         goto w_Same2;
   w_Uzh:
         zh = vh;
         zhchng();
   w_Same2:
         if (zl LT vl)  goto w_Uzl;
         if (zl EQ vl)  goto w_Exit;
   w_MUxl:
         lowerbd((zl + ul),vl);
         if (xl GE vl)  goto w_Exit;
   w_Uxl:
         xl = vl;
         xlchng();
         goto w_Exit;
   w_Uzl:
         zl = vl;
         zlchng();
   w_Exit:
         success();
end_op(wrap)


