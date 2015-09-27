#ifdef USE_LUA_SCRIPT

/*
** Lua binding: CasaEngine
** Generated automatically by tolua++-1.0.92 on 02/11/15 16:59:42.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CasaEngine_open (lua_State* tolua_S);

#include "required.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CasaEngine__Matrix4 (lua_State* tolua_S)
{
 CasaEngine::Matrix4* self = (CasaEngine::Matrix4*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__EventArgs (lua_State* tolua_S)
{
 CasaEngine::EventArgs* self = (CasaEngine::EventArgs*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__Quaternion (lua_State* tolua_S)
{
 CasaEngine::Quaternion* self = (CasaEngine::Quaternion*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CVector4_float_ (lua_State* tolua_S)
{
 CasaEngine::CVector4<float>* self = (CasaEngine::CVector4<float>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CPlane (lua_State* tolua_S)
{
 CasaEngine::CPlane* self = (CasaEngine::CPlane*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CVector2_float_ (lua_State* tolua_S)
{
 CasaEngine::CVector2<float>* self = (CasaEngine::CVector2<float>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CRectangle (lua_State* tolua_S)
{
 CasaEngine::CRectangle* self = (CasaEngine::CRectangle*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CVector2_int_ (lua_State* tolua_S)
{
 CasaEngine::CVector2<int>* self = (CasaEngine::CVector2<int>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__CVector3_float_ (lua_State* tolua_S)
{
 CasaEngine::CVector3<float>* self = (CasaEngine::CVector3<float>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CasaEngine__Matrix3 (lua_State* tolua_S)
{
 CasaEngine::Matrix3* self = (CasaEngine::Matrix3*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CasaEngine::EventConnection");
 tolua_usertype(tolua_S,"CasaEngine::EventSet");
 tolua_usertype(tolua_S,"CasaEngine::IOManager");
 tolua_usertype(tolua_S,"CasaEngine::CRectangle");
 tolua_usertype(tolua_S,"CasaEngine::CVector2<int>");
 tolua_usertype(tolua_S,"CasaEngine::LogManager");
 tolua_usertype(tolua_S,"CasaEngine::Matrix4");
 tolua_usertype(tolua_S,"CasaEngine::File");
 tolua_usertype(tolua_S,"CasaEngine::GlobalEventSet");
 tolua_usertype(tolua_S,"std::vector<CasaEngine::CVector3<float> >");
 tolua_usertype(tolua_S,"CasaEngine::Quaternion");
 tolua_usertype(tolua_S,"CasaEngine::Event");
 tolua_usertype(tolua_S,"CasaEngine::CVector4<float>");
 tolua_usertype(tolua_S,"CasaEngine::CPlane");
 tolua_usertype(tolua_S,"CasaEngine::IFile");
 tolua_usertype(tolua_S,"CasaEngine::EventArgs");
 tolua_usertype(tolua_S,"CasaEngine::CVector3<float>");
 tolua_usertype(tolua_S,"CasaEngine::CVector2<float>");
 tolua_usertype(tolua_S,"std::vector<CasaEngine::CVector2<float> >");
 tolua_usertype(tolua_S,"sf::Keyboard");
 tolua_usertype(tolua_S,"sf::Mouse");
 tolua_usertype(tolua_S,"CasaEngine::Matrix3");
}

/* method: Zero of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Zero00
static int tolua_CasaEngine_CasaEngine_Vector2I_Zero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  CasaEngine::CVector2<int>::Zero();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Zero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: One of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_One00
static int tolua_CasaEngine_CasaEngine_Vector2I_One00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  CasaEngine::CVector2<int>::One();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'One'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitX of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_UnitX00
static int tolua_CasaEngine_CasaEngine_Vector2I_UnitX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  CasaEngine::CVector2<int>::UnitX();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitY of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_UnitY00
static int tolua_CasaEngine_CasaEngine_Vector2I_UnitY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  CasaEngine::CVector2<int>::UnitY();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_new00
static int tolua_CasaEngine_CasaEngine_Vector2I_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int X = ((int)  tolua_tonumber(tolua_S,2,0));
  int Y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::CVector2<int>* tolua_ret = (CasaEngine::CVector2<int>*)  Mtolua_new((CasaEngine::CVector2<int>)(X,Y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector2<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_new00_local
static int tolua_CasaEngine_CasaEngine_Vector2I_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int X = ((int)  tolua_tonumber(tolua_S,2,0));
  int Y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::CVector2<int>* tolua_ret = (CasaEngine::CVector2<int>*)  Mtolua_new((CasaEngine::CVector2<int>)(X,Y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Set00
static int tolua_CasaEngine_CasaEngine_Vector2I_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<int>* self = (CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  int X = ((int)  tolua_tonumber(tolua_S,2,0));
  int Y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(X,Y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_getX00
static int tolua_CasaEngine_CasaEngine_Vector2I_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_getY00
static int tolua_CasaEngine_CasaEngine_Vector2I_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsZero of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_IsZero00
static int tolua_CasaEngine_CasaEngine_Vector2I_IsZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsZero'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Length00
static int tolua_CasaEngine_CasaEngine_Vector2I_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LengthSq of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_LengthSq00
static int tolua_CasaEngine_CasaEngine_Vector2I_LengthSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LengthSq'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LengthSquared();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LengthSq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Normalize00
static int tolua_CasaEngine_CasaEngine_Vector2I_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<int>* self = (CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   self->Normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dot of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Dot00
static int tolua_CasaEngine_CasaEngine_Vector2I_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v2 = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Dot(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Sign of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Sign00
static int tolua_CasaEngine_CasaEngine_Vector2I_Sign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v2 = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Sign'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Sign(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrthogonal of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Perp00
static int tolua_CasaEngine_CasaEngine_Vector2I_Perp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrthogonal'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->GetOrthogonal();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrthogonal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Truncate of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Truncate00
static int tolua_CasaEngine_CasaEngine_Vector2I_Truncate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<int>* self = (CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  float max = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Truncate'", NULL);
#endif
  {
   self->Truncate(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Truncate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Distance of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Distance00
static int tolua_CasaEngine_CasaEngine_Vector2I_Distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v2 = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Distance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Distance(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Distance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DistanceSq of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_DistanceSq00
static int tolua_CasaEngine_CasaEngine_Vector2I_DistanceSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v2 = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DistanceSq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->DistanceSq(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DistanceSq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reflect of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_Reflect00
static int tolua_CasaEngine_CasaEngine_Vector2I_Reflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<int>* self = (CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* norm = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reflect'", NULL);
#endif
  {
   self->Reflect(*norm);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reflect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReverse of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I_GetReverse00
static int tolua_CasaEngine_CasaEngine_Vector2I_GetReverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReverse'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->GetReverse();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I__add00
static int tolua_CasaEngine_CasaEngine_Vector2I__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I__sub00
static int tolua_CasaEngine_CasaEngine_Vector2I__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I__mul00
static int tolua_CasaEngine_CasaEngine_Vector2I__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  int t = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->operator*(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I__div00
static int tolua_CasaEngine_CasaEngine_Vector2I__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  int t = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->operator/(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CVector2<int> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2I__eq00
static int tolua_CasaEngine_CasaEngine_Vector2I__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<int>* self = (const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* v = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Zero of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Zero00
static int tolua_CasaEngine_CasaEngine_Vector2F_Zero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  CasaEngine::CVector2<float>::Zero();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Zero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: One of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_One00
static int tolua_CasaEngine_CasaEngine_Vector2F_One00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  CasaEngine::CVector2<float>::One();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'One'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitX of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_UnitX00
static int tolua_CasaEngine_CasaEngine_Vector2F_UnitX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  CasaEngine::CVector2<float>::UnitX();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitY of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_UnitY00
static int tolua_CasaEngine_CasaEngine_Vector2F_UnitY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  CasaEngine::CVector2<float>::UnitY();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_new00
static int tolua_CasaEngine_CasaEngine_Vector2F_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::CVector2<float>* tolua_ret = (CasaEngine::CVector2<float>*)  Mtolua_new((CasaEngine::CVector2<float>)(X,Y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector2<float>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_new00_local
static int tolua_CasaEngine_CasaEngine_Vector2F_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::CVector2<float>* tolua_ret = (CasaEngine::CVector2<float>*)  Mtolua_new((CasaEngine::CVector2<float>)(X,Y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Set00
static int tolua_CasaEngine_CasaEngine_Vector2F_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<float>* self = (CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(X,Y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_getX00
static int tolua_CasaEngine_CasaEngine_Vector2F_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_getY00
static int tolua_CasaEngine_CasaEngine_Vector2F_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsZero of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_IsZero00
static int tolua_CasaEngine_CasaEngine_Vector2F_IsZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsZero'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Length00
static int tolua_CasaEngine_CasaEngine_Vector2F_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LengthSq of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_LengthSq00
static int tolua_CasaEngine_CasaEngine_Vector2F_LengthSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LengthSq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->LengthSquared();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LengthSquared'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Normalize00
static int tolua_CasaEngine_CasaEngine_Vector2F_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<float>* self = (CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   self->Normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dot of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Dot00
static int tolua_CasaEngine_CasaEngine_Vector2F_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v2 = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Dot(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Sign of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Sign00
static int tolua_CasaEngine_CasaEngine_Vector2F_Sign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v2 = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Sign'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Sign(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrthogonal of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Perp00
static int tolua_CasaEngine_CasaEngine_Vector2F_Perp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrthogonal'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->GetOrthogonal();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrthogonal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Truncate of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Truncate00
static int tolua_CasaEngine_CasaEngine_Vector2F_Truncate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<float>* self = (CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  float max = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Truncate'", NULL);
#endif
  {
   self->Truncate(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Truncate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Distance of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Distance00
static int tolua_CasaEngine_CasaEngine_Vector2F_Distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v2 = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Distance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Distance(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Distance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DistanceSq of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_DistanceSq00
static int tolua_CasaEngine_CasaEngine_Vector2F_DistanceSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v2 = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DistanceSq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->DistanceSq(*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DistanceSq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reflect of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_Reflect00
static int tolua_CasaEngine_CasaEngine_Vector2F_Reflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector2<float>* self = (CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* norm = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reflect'", NULL);
#endif
  {
   self->Reflect(*norm);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reflect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReverse of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F_GetReverse00
static int tolua_CasaEngine_CasaEngine_Vector2F_GetReverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReverse'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->GetReverse();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F__add00
static int tolua_CasaEngine_CasaEngine_Vector2F__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F__sub00
static int tolua_CasaEngine_CasaEngine_Vector2F__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F__mul00
static int tolua_CasaEngine_CasaEngine_Vector2F__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  float t = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->operator*(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F__div00
static int tolua_CasaEngine_CasaEngine_Vector2F__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  float t = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->operator/(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CVector2<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector2F__eq00
static int tolua_CasaEngine_CasaEngine_Vector2F__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector2<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector2<float>* self = (const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Zero of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Zero00
static int tolua_CasaEngine_CasaEngine_Vector3F_Zero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Zero();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Zero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: One of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_One00
static int tolua_CasaEngine_CasaEngine_Vector3F_One00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::One();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'One'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitX of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_UnitX00
static int tolua_CasaEngine_CasaEngine_Vector3F_UnitX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::UnitX();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitY of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_UnitY00
static int tolua_CasaEngine_CasaEngine_Vector3F_UnitY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::UnitY();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitZ of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_UnitZ00
static int tolua_CasaEngine_CasaEngine_Vector3F_UnitZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::UnitZ();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Up of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Up00
static int tolua_CasaEngine_CasaEngine_Vector3F_Up00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Up();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Up'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Down of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Down00
static int tolua_CasaEngine_CasaEngine_Vector3F_Down00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Down();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Down'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Right of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Right00
static int tolua_CasaEngine_CasaEngine_Vector3F_Right00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Right();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Right'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Left of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Left00
static int tolua_CasaEngine_CasaEngine_Vector3F_Left00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Left();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Left'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Forward of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Forward00
static int tolua_CasaEngine_CasaEngine_Vector3F_Forward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Forward();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Forward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Backward of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Backward00
static int tolua_CasaEngine_CasaEngine_Vector3F_Backward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Backward();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Backward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dot of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Dot00
static int tolua_CasaEngine_CasaEngine_Vector3F_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* v1 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* v2 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   float tolua_ret = (float)  CasaEngine::CVector3<float>::Dot(*v1,*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cross of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Cross00
static int tolua_CasaEngine_CasaEngine_Vector3F_Cross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* v1 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* v2 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  CasaEngine::CVector3<float>::Cross(*v1,*v2);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_new00
static int tolua_CasaEngine_CasaEngine_Vector3F_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CasaEngine::CVector3<float>* tolua_ret = (CasaEngine::CVector3<float>*)  Mtolua_new((CasaEngine::CVector3<float>)(X,Y,Z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector3<float>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_new00_local
static int tolua_CasaEngine_CasaEngine_Vector3F_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CasaEngine::CVector3<float>* tolua_ret = (CasaEngine::CVector3<float>*)  Mtolua_new((CasaEngine::CVector3<float>)(X,Y,Z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Set00
static int tolua_CasaEngine_CasaEngine_Vector3F_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector3<float>* self = (CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(X,Y,Z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_getX00
static int tolua_CasaEngine_CasaEngine_Vector3F_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_getY00
static int tolua_CasaEngine_CasaEngine_Vector3F_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZ of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_getZ00
static int tolua_CasaEngine_CasaEngine_Vector3F_getZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsZero of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_IsZero00
static int tolua_CasaEngine_CasaEngine_Vector3F_IsZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsZero'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Length00
static int tolua_CasaEngine_CasaEngine_Vector3F_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LengthSquared of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_LengthSq00
static int tolua_CasaEngine_CasaEngine_Vector3F_LengthSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LengthSquared'", NULL);
#endif
  {
   float tolua_ret = (float)  self->LengthSquared();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LengthSq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F_Normalize00
static int tolua_CasaEngine_CasaEngine_Vector3F_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector3<float>* self = (CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   self->Normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F__add00
static int tolua_CasaEngine_CasaEngine_Vector3F__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F__sub00
static int tolua_CasaEngine_CasaEngine_Vector3F__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CVector3<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector3F__eq00
static int tolua_CasaEngine_CasaEngine_Vector3F__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector3<float>* self = (const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_new00
static int tolua_CasaEngine_CasaEngine_Vector4F_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  float W = ((float)  tolua_tonumber(tolua_S,5,1));
  {
   CasaEngine::CVector4<float>* tolua_ret = (CasaEngine::CVector4<float>*)  Mtolua_new((CasaEngine::CVector4<float>)(X,Y,Z,W));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector4<float>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_new00_local
static int tolua_CasaEngine_CasaEngine_Vector4F_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  float W = ((float)  tolua_tonumber(tolua_S,5,1));
  {
   CasaEngine::CVector4<float>* tolua_ret = (CasaEngine::CVector4<float>*)  Mtolua_new((CasaEngine::CVector4<float>)(X,Y,Z,W));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_Set00
static int tolua_CasaEngine_CasaEngine_Vector4F_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector4<float>* self = (CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  float W = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(X,Y,Z,W);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_getX00
static int tolua_CasaEngine_CasaEngine_Vector4F_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_getY00
static int tolua_CasaEngine_CasaEngine_Vector4F_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZ of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_getZ00
static int tolua_CasaEngine_CasaEngine_Vector4F_getZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getW of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_getW00
static int tolua_CasaEngine_CasaEngine_Vector4F_getW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getW'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getW();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_Length00
static int tolua_CasaEngine_CasaEngine_Vector4F_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LengthSq of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_LengthSq00
static int tolua_CasaEngine_CasaEngine_Vector4F_LengthSq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LengthSq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->LengthSquared();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LengthSquared'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F_Normalize00
static int tolua_CasaEngine_CasaEngine_Vector4F_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CVector4<float>* self = (CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   self->Normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F__add00
static int tolua_CasaEngine_CasaEngine_Vector4F__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector4<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector4<float>* v = ((const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::CVector4<float> tolua_ret = (CasaEngine::CVector4<float>)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector4<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector4<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F__sub00
static int tolua_CasaEngine_CasaEngine_Vector4F__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector4<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector4<float>* v = ((const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::CVector4<float> tolua_ret = (CasaEngine::CVector4<float>)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector4<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector4<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F__mul00
static int tolua_CasaEngine_CasaEngine_Vector4F__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  float t = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::CVector4<float> tolua_ret = (CasaEngine::CVector4<float>)  self->operator*(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector4<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector4<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F__div00
static int tolua_CasaEngine_CasaEngine_Vector4F__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  float t = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CasaEngine::CVector4<float> tolua_ret = (CasaEngine::CVector4<float>)  self->operator/(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector4<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector4<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CVector4<float> */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Vector4F__eq00
static int tolua_CasaEngine_CasaEngine_Vector4F__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CVector4<float>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector4<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CVector4<float>* self = (const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector4<float>* v = ((const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_new00
static int tolua_CasaEngine_CasaEngine_Matrix3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float m11 = ((float)  tolua_tonumber(tolua_S,2,1.0f));
  float m12 = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float m13 = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float m21 = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float m22 = ((float)  tolua_tonumber(tolua_S,6,1.0f));
  float m23 = ((float)  tolua_tonumber(tolua_S,7,0.0f));
  float m31 = ((float)  tolua_tonumber(tolua_S,8,0.0f));
  float m32 = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float m33 = ((float)  tolua_tonumber(tolua_S,10,1.0f));
  {
   CasaEngine::Matrix3* tolua_ret = (CasaEngine::Matrix3*)  Mtolua_new((CasaEngine::Matrix3)(m11,m12,m13,m21,m22,m23,m31,m32,m33));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Matrix3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_new00_local
static int tolua_CasaEngine_CasaEngine_Matrix3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float m11 = ((float)  tolua_tonumber(tolua_S,2,1.0f));
  float m12 = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float m13 = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float m21 = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float m22 = ((float)  tolua_tonumber(tolua_S,6,1.0f));
  float m23 = ((float)  tolua_tonumber(tolua_S,7,0.0f));
  float m31 = ((float)  tolua_tonumber(tolua_S,8,0.0f));
  float m32 = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float m33 = ((float)  tolua_tonumber(tolua_S,10,1.0f));
  {
   CasaEngine::Matrix3* tolua_ret = (CasaEngine::Matrix3*)  Mtolua_new((CasaEngine::Matrix3)(m11,m12,m13,m21,m22,m23,m31,m32,m33));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Identity of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Identity00
static int tolua_CasaEngine_CasaEngine_Matrix3_Identity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Identity'", NULL);
#endif
  {
   self->Identity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Identity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Determinant of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Determinant00
static int tolua_CasaEngine_CasaEngine_Matrix3_Determinant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Determinant'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Determinant();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Determinant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transpose of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Transpose00
static int tolua_CasaEngine_CasaEngine_Matrix3_Transpose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transpose'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->Transpose();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transpose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Inverse of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Inverse00
static int tolua_CasaEngine_CasaEngine_Matrix3_Inverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Inverse'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->Inverse();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Inverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateTranslation of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_CreateTranslation00
static int tolua_CasaEngine_CasaEngine_Matrix3_CreateTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateTranslation'", NULL);
#endif
  {
   self->CreateTranslation(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateScaling of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_CreateScaling00
static int tolua_CasaEngine_CasaEngine_Matrix3_CreateScaling00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateScaling'", NULL);
#endif
  {
   self->CreateScaling(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateScaling'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotation of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation00
static int tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotation'", NULL);
#endif
  {
   self->CreateRotation(Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotation of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation01
static int tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const CasaEngine::CVector2<float>* Center = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotation'", NULL);
#endif
  {
   self->CreateRotation(Angle,*Center);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Translate of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Translate00
static int tolua_CasaEngine_CasaEngine_Matrix3_Translate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Translate'", NULL);
#endif
  {
   self->Translate(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Translate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Scale of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Scale00
static int tolua_CasaEngine_CasaEngine_Matrix3_Scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'", NULL);
#endif
  {
   self->Scale(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Rotate of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Rotate00
static int tolua_CasaEngine_CasaEngine_Matrix3_Rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'", NULL);
#endif
  {
   self->Rotate(Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Rotate of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Rotate01
static int tolua_CasaEngine_CasaEngine_Matrix3_Rotate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* fwd = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector2<float>* side = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'", NULL);
#endif
  {
   self->Rotate(*fwd,*side);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix3_Rotate00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTranslation of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_GetTranslation00
static int tolua_CasaEngine_CasaEngine_Matrix3_GetTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTranslation'", NULL);
#endif
  {
   CasaEngine::CVector2<float> tolua_ret = (CasaEngine::CVector2<float>)  self->GetTranslation();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Transform00
static int tolua_CasaEngine_CasaEngine_Matrix3_Transform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<float>* v = ((const CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
  float w = ((float)  tolua_tonumber(tolua_S,3,1.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->Transform(*v,w);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_Transform01
static int tolua_CasaEngine_CasaEngine_Matrix3_Transform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->Transform(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix3_Transform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: TransformVector2List of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2List00
static int tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2List00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<CasaEngine::CVector2<float> >",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  std::vector<CasaEngine::CVector2<float> >* vPoint_ = ((std::vector<CasaEngine::CVector2<float> >*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransformVector2List'", NULL);
#endif
  {
   self->TransformVector2List(*vPoint_);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TransformVector2List'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TransformVector2F of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2F00
static int tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2F00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CasaEngine::CVector2<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix3* self = (CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  CasaEngine::CVector2<float>* vPoint = ((CasaEngine::CVector2<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransformVector2F'", NULL);
#endif
  {
   self->TransformVector2F(*vPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TransformVector2F'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__add00
static int tolua_CasaEngine_CasaEngine_Matrix3__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->operator+();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__sub00
static int tolua_CasaEngine_CasaEngine_Matrix3__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__add01
static int tolua_CasaEngine_CasaEngine_Matrix3__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix3* m = ((const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->operator+(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix3__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__sub01
static int tolua_CasaEngine_CasaEngine_Matrix3__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix3* m = ((const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->operator-(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix3__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__mul00
static int tolua_CasaEngine_CasaEngine_Matrix3__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix3* m = ((const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::Matrix3 tolua_ret = (CasaEngine::Matrix3)  self->operator*(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix3));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::Matrix3 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix3__eq00
static int tolua_CasaEngine_CasaEngine_Matrix3__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix3",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix3* self = (const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix3* m = ((const CasaEngine::Matrix3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*m);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_new00
static int tolua_CasaEngine_CasaEngine_Matrix4_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,17,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,18,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float m11 = ((float)  tolua_tonumber(tolua_S,2,1.0f));
  float m12 = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float m13 = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float m14 = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float m21 = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  float m22 = ((float)  tolua_tonumber(tolua_S,7,1.0f));
  float m23 = ((float)  tolua_tonumber(tolua_S,8,0.0f));
  float m24 = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float m31 = ((float)  tolua_tonumber(tolua_S,10,0.0f));
  float m32 = ((float)  tolua_tonumber(tolua_S,11,0.0f));
  float m33 = ((float)  tolua_tonumber(tolua_S,12,1.0f));
  float m34 = ((float)  tolua_tonumber(tolua_S,13,0.0f));
  float m41 = ((float)  tolua_tonumber(tolua_S,14,0.0f));
  float m42 = ((float)  tolua_tonumber(tolua_S,15,0.0f));
  float m43 = ((float)  tolua_tonumber(tolua_S,16,0.0f));
  float m44 = ((float)  tolua_tonumber(tolua_S,17,1.0f));
  {
   CasaEngine::Matrix4* tolua_ret = (CasaEngine::Matrix4*)  Mtolua_new((CasaEngine::Matrix4)(m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Matrix4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_new00_local
static int tolua_CasaEngine_CasaEngine_Matrix4_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,17,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,18,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float m11 = ((float)  tolua_tonumber(tolua_S,2,1.0f));
  float m12 = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float m13 = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float m14 = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float m21 = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  float m22 = ((float)  tolua_tonumber(tolua_S,7,1.0f));
  float m23 = ((float)  tolua_tonumber(tolua_S,8,0.0f));
  float m24 = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float m31 = ((float)  tolua_tonumber(tolua_S,10,0.0f));
  float m32 = ((float)  tolua_tonumber(tolua_S,11,0.0f));
  float m33 = ((float)  tolua_tonumber(tolua_S,12,1.0f));
  float m34 = ((float)  tolua_tonumber(tolua_S,13,0.0f));
  float m41 = ((float)  tolua_tonumber(tolua_S,14,0.0f));
  float m42 = ((float)  tolua_tonumber(tolua_S,15,0.0f));
  float m43 = ((float)  tolua_tonumber(tolua_S,16,0.0f));
  float m44 = ((float)  tolua_tonumber(tolua_S,17,1.0f));
  {
   CasaEngine::Matrix4* tolua_ret = (CasaEngine::Matrix4*)  Mtolua_new((CasaEngine::Matrix4)(m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Identity of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Identity00
static int tolua_CasaEngine_CasaEngine_Matrix4_Identity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Identity'", NULL);
#endif
  {
   self->Identity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Identity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Determinant of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Determinant00
static int tolua_CasaEngine_CasaEngine_Matrix4_Determinant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Determinant'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Determinant();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Determinant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transpose of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transpose00
static int tolua_CasaEngine_CasaEngine_Matrix4_Transpose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transpose'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->Transpose();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transpose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Invert of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Invert00
static int tolua_CasaEngine_CasaEngine_Matrix4_Invert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Invert'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->Invert();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Invert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTranslation of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation00
static int tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTranslation'", NULL);
#endif
  {
   self->SetTranslation(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTranslation of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation01
static int tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  CasaEngine::CVector3<float> trans_ = *((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTranslation'", NULL);
#endif
  {
   self->SetTranslation(trans_);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateTranslation of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateTranslation00
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateTranslation'", NULL);
#endif
  {
   self->CreateTranslation(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateScale of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateScale00
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateScale'", NULL);
#endif
  {
   self->CreateScale(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationX of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX00
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationX'", NULL);
#endif
  {
   self->CreateRotationX(Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationY of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY00
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationY'", NULL);
#endif
  {
   self->CreateRotationY(Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationZ of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ00
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationZ'", NULL);
#endif
  {
   self->CreateRotationZ(Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRotationZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationX of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX01
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const CasaEngine::CVector3<float>* Center = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationX'", NULL);
#endif
  {
   self->CreateRotationX(Angle,*Center);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationY of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY01
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const CasaEngine::CVector3<float>* Center = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationY'", NULL);
#endif
  {
   self->CreateRotationY(Angle,*Center);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRotationZ of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ01
static int tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const CasaEngine::CVector3<float>* Center = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRotationZ'", NULL);
#endif
  {
   self->CreateRotationZ(Angle,*Center);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTranslation of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_GetTranslation00
static int tolua_CasaEngine_CasaEngine_Matrix4_GetTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTranslation'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->GetTranslation();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transformation of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transformation00
static int tolua_CasaEngine_CasaEngine_Matrix4_Transformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"const CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"const CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* pscalingcenter = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::Quaternion* pscalingrotation = ((const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,3,0));
  const CasaEngine::CVector3<float>* pscaling = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
  const CasaEngine::CVector3<float>* protationcenter = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,5,0));
  const CasaEngine::Quaternion* protation = ((const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,6,0));
  const CasaEngine::CVector3<float>* ptranslation = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transformation'", NULL);
#endif
  {
   self->Transformation(pscalingcenter,pscalingrotation,pscaling,protationcenter,protation,ptranslation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transform00
static int tolua_CasaEngine_CasaEngine_Matrix4_Transform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  float w = ((float)  tolua_tonumber(tolua_S,3,1.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   CasaEngine::CVector3<float> tolua_ret = (CasaEngine::CVector3<float>)  self->Transform(*v,w);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector3<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector3<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector3<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transform01
static int tolua_CasaEngine_CasaEngine_Matrix4_Transform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector4<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector4<float>* v = ((const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   CasaEngine::CVector4<float> tolua_ret = (CasaEngine::CVector4<float>)  self->Transform(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector4<float>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector4<float>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector4<float>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_Transform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transform02
static int tolua_CasaEngine_CasaEngine_Matrix4_Transform02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* position = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  CasaEngine::CVector3<float>* result = ((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   self->Transform(*position,*result);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_Transform01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_Transform03
static int tolua_CasaEngine_CasaEngine_Matrix4_Transform03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const std::vector<CasaEngine::CVector3<float> >",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<CasaEngine::CVector3<float> >",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const std::vector<CasaEngine::CVector3<float> >* sourceArray = ((const std::vector<CasaEngine::CVector3<float> >*)  tolua_tousertype(tolua_S,2,0));
  std::vector<CasaEngine::CVector3<float> >* destinationArray = ((std::vector<CasaEngine::CVector3<float> >*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   self->Transform(*sourceArray,*destinationArray);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_Transform02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: TransformNormal of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_TransformNormal00
static int tolua_CasaEngine_CasaEngine_Matrix4_TransformNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* normal = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  CasaEngine::CVector3<float>* result = ((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransformNormal'", NULL);
#endif
  {
   self->TransformNormal(*normal,*result);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TransformNormal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OrthoOffCenter of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_OrthoOffCenter00
static int tolua_CasaEngine_CasaEngine_Matrix4_OrthoOffCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Left = ((float)  tolua_tonumber(tolua_S,2,0));
  float Top = ((float)  tolua_tonumber(tolua_S,3,0));
  float Right = ((float)  tolua_tonumber(tolua_S,4,0));
  float Bottom = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OrthoOffCenter'", NULL);
#endif
  {
   self->OrthoOffCenter(Left,Top,Right,Bottom);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OrthoOffCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PerspectiveFOV of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_PerspectiveFOV00
static int tolua_CasaEngine_CasaEngine_Matrix4_PerspectiveFOV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  float Fov = ((float)  tolua_tonumber(tolua_S,2,0));
  float Ratio = ((float)  tolua_tonumber(tolua_S,3,0));
  float Near = ((float)  tolua_tonumber(tolua_S,4,0));
  float Far = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PerspectiveFOV'", NULL);
#endif
  {
   self->PerspectiveFOV(Fov,Ratio,Near,Far);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PerspectiveFOV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LookAt of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_LookAt00
static int tolua_CasaEngine_CasaEngine_Matrix4_LookAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* From = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* To = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LookAt'", NULL);
#endif
  {
   self->LookAt(*From,*To);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LookAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LookAt of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4_LookAt01
static int tolua_CasaEngine_CasaEngine_Matrix4_LookAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::Matrix4* self = (CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* From = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* To = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  const CasaEngine::CVector3<float>* Up = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LookAt'", NULL);
#endif
  {
   self->LookAt(*From,*To,*Up);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4_LookAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__add00
static int tolua_CasaEngine_CasaEngine_Matrix4__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->operator+();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__sub00
static int tolua_CasaEngine_CasaEngine_Matrix4__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__add01
static int tolua_CasaEngine_CasaEngine_Matrix4__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix4* m = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->operator+(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__sub01
static int tolua_CasaEngine_CasaEngine_Matrix4__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix4* m = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->operator-(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Matrix4__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__mul00
static int tolua_CasaEngine_CasaEngine_Matrix4__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix4* m = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->operator*(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::Matrix4 */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Matrix4__eq00
static int tolua_CasaEngine_CasaEngine_Matrix4__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Matrix4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Matrix4* self = (const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix4* m = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*m);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new00
static int tolua_CasaEngine_CasaEngine_Quaternion_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0.0f));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float W = ((float)  tolua_tonumber(tolua_S,5,1.0f));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(X,Y,Z,W));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new00_local
static int tolua_CasaEngine_CasaEngine_Quaternion_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0.0f));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float W = ((float)  tolua_tonumber(tolua_S,5,1.0f));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(X,Y,Z,W));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new01
static int tolua_CasaEngine_CasaEngine_Quaternion_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix4* Matrix = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(*Matrix));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Quaternion_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new01_local
static int tolua_CasaEngine_CasaEngine_Quaternion_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Matrix4* Matrix = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(*Matrix));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Quaternion_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new02
static int tolua_CasaEngine_CasaEngine_Quaternion_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* Axis = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  float Angle = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(*Axis,Angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Quaternion_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_new02_local
static int tolua_CasaEngine_CasaEngine_Quaternion_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* Axis = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  float Angle = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::Quaternion* tolua_ret = (CasaEngine::Quaternion*)  Mtolua_new((CasaEngine::Quaternion)(*Axis,Angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Quaternion_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Identity of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_Identity00
static int tolua_CasaEngine_CasaEngine_Quaternion_Identity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Quaternion* self = (CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Identity'", NULL);
#endif
  {
   self->Identity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Identity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_Normalize00
static int tolua_CasaEngine_CasaEngine_Quaternion_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Quaternion* self = (CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   self->Normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Conjugate of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_Conjugate00
static int tolua_CasaEngine_CasaEngine_Quaternion_Conjugate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Conjugate'", NULL);
#endif
  {
   CasaEngine::Quaternion tolua_ret = (CasaEngine::Quaternion)  self->Conjugate();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Quaternion)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Quaternion));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Conjugate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToMatrix4 of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_ToMatrix00
static int tolua_CasaEngine_CasaEngine_Quaternion_ToMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToMatrix4'", NULL);
#endif
  {
   CasaEngine::Matrix4 tolua_ret = (CasaEngine::Matrix4)  self->ToMatrix4();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToMatrix4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FromMatrix of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_FromMatrix00
static int tolua_CasaEngine_CasaEngine_Quaternion_FromMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Matrix4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Quaternion* self = (CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Matrix4* Matrix = ((const CasaEngine::Matrix4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FromMatrix'", NULL);
#endif
  {
   self->FromMatrix(*Matrix);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FromMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FromAxisAngle of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_FromAxisAngle00
static int tolua_CasaEngine_CasaEngine_Quaternion_FromAxisAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Quaternion* self = (CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* Axis = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  float Angle = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FromAxisAngle'", NULL);
#endif
  {
   self->FromAxisAngle(*Axis,Angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FromAxisAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToAxisAngle of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_ToAxisAngle00
static int tolua_CasaEngine_CasaEngine_Quaternion_ToAxisAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  CasaEngine::CVector3<float>* Axis = ((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  float Angle = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToAxisAngle'", NULL);
#endif
  {
   self->ToAxisAngle(*Axis,Angle);
   tolua_pushnumber(tolua_S,(lua_Number)Angle);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToAxisAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_Transform00
static int tolua_CasaEngine_CasaEngine_Quaternion_Transform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* value = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  CasaEngine::CVector3<float>* result = ((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   self->Transform(*value,*result);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Transform of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_Transform01
static int tolua_CasaEngine_CasaEngine_Quaternion_Transform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const std::vector<CasaEngine::CVector3<float> >",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<CasaEngine::CVector3<float> >",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  const std::vector<CasaEngine::CVector3<float> >* sourceArray = ((const std::vector<CasaEngine::CVector3<float> >*)  tolua_tousertype(tolua_S,2,0));
  std::vector<CasaEngine::CVector3<float> >* destinationArray = ((std::vector<CasaEngine::CVector3<float> >*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'", NULL);
#endif
  {
   self->Transform(*sourceArray,*destinationArray);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_Quaternion_Transform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: FromEulerAngles of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion_FromEulerAngles00
static int tolua_CasaEngine_CasaEngine_Quaternion_FromEulerAngles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::Quaternion",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::Quaternion* self = (CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FromEulerAngles'", NULL);
#endif
  {
   self->FromEulerAngles(X,Y,Z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FromEulerAngles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CasaEngine::Quaternion */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Quaternion__mul00
static int tolua_CasaEngine_CasaEngine_Quaternion__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Quaternion",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Quaternion* self = (const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::Quaternion* q_ = ((const CasaEngine::Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CasaEngine::Quaternion tolua_ret = (CasaEngine::Quaternion)  self->operator*(*q_);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::Quaternion)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::Quaternion));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new00
static int tolua_CasaEngine_CasaEngine_CPlane_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float A = ((float)  tolua_tonumber(tolua_S,2,0.0f));
  float B = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float C = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float D = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(A,B,C,D));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new00_local
static int tolua_CasaEngine_CasaEngine_CPlane_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float A = ((float)  tolua_tonumber(tolua_S,2,0.0f));
  float B = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float C = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float D = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(A,B,C,D));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new01
static int tolua_CasaEngine_CasaEngine_CPlane_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* v0 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* v1 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  const CasaEngine::CVector3<float>* v2 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(*v0,*v1,*v2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CPlane_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new01_local
static int tolua_CasaEngine_CasaEngine_CPlane_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* v0 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* v1 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  const CasaEngine::CVector3<float>* v2 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(*v0,*v1,*v2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CPlane_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new02
static int tolua_CasaEngine_CasaEngine_CPlane_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* Normal = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* Point = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(*Normal,*Point));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CPlane_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_new02_local
static int tolua_CasaEngine_CasaEngine_CPlane_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector3<float>* Normal = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* Point = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   CasaEngine::CPlane* tolua_ret = (CasaEngine::CPlane*)  Mtolua_new((CasaEngine::CPlane)(*Normal,*Point));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CPlane");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CPlane_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BuildFromPoints of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_BuildFromPoints00
static int tolua_CasaEngine_CasaEngine_CPlane_BuildFromPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CPlane* self = (CasaEngine::CPlane*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* v0 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* v1 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  const CasaEngine::CVector3<float>* v2 = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BuildFromPoints'", NULL);
#endif
  {
   self->BuildFromPoints(*v0,*v1,*v2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BuildFromPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DistanceToPoint of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint00
static int tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CPlane* self = (const CasaEngine::CPlane*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* Point = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DistanceToPoint'", NULL);
#endif
  {
   float tolua_ret = (float)  self->DistanceToPoint(*Point);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DistanceToPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DistanceToPoint of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint01
static int tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector4<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CPlane* self = (const CasaEngine::CPlane*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector4<float>* Point = ((const CasaEngine::CVector4<float>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DistanceToPoint'", NULL);
#endif
  {
   float tolua_ret = (float)  self->DistanceToPoint(*Point);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IntersectLine of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane_IntersectLine00
static int tolua_CasaEngine_CasaEngine_CPlane_IntersectLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector3<float>",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"CasaEngine::CVector3<float>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CPlane* self = (CasaEngine::CPlane*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector3<float>* p1_ = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector3<float>* p2_ = ((const CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,3,0));
  CasaEngine::CVector3<float>* pOut_ = ((CasaEngine::CVector3<float>*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IntersectLine'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IntersectLine(*p1_,*p2_,pOut_);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IntersectLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CPlane */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CPlane__eq00
static int tolua_CasaEngine_CasaEngine_CPlane__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CPlane",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CPlane",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CPlane* self = (const CasaEngine::CPlane*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CPlane* p = ((const CasaEngine::CPlane*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new00
static int tolua_CasaEngine_CasaEngine_CRectangle_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new00_local
static int tolua_CasaEngine_CasaEngine_CRectangle_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new01
static int tolua_CasaEngine_CasaEngine_CRectangle_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector2<int>* Start = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(*Start));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new01_local
static int tolua_CasaEngine_CasaEngine_CRectangle_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector2<int>* Start = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(*Start));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new02
static int tolua_CasaEngine_CasaEngine_CRectangle_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector2<int>* Start = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector2<int>* Size = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(*Start,*Size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new02_local
static int tolua_CasaEngine_CasaEngine_CRectangle_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CVector2<int>* Start = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
  const CasaEngine::CVector2<int>* Size = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(*Start,*Size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new03
static int tolua_CasaEngine_CasaEngine_CRectangle_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int Left = ((int)  tolua_tonumber(tolua_S,2,0));
  int Top = ((int)  tolua_tonumber(tolua_S,3,0));
  int Width = ((int)  tolua_tonumber(tolua_S,4,0));
  int Height = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(Left,Top,Width,Height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_new03_local
static int tolua_CasaEngine_CasaEngine_CRectangle_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int Left = ((int)  tolua_tonumber(tolua_S,2,0));
  int Top = ((int)  tolua_tonumber(tolua_S,3,0));
  int Width = ((int)  tolua_tonumber(tolua_S,4,0));
  int Height = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CasaEngine::CRectangle* tolua_ret = (CasaEngine::CRectangle*)  Mtolua_new((CasaEngine::CRectangle)(Left,Top,Width,Height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::CRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Set00
static int tolua_CasaEngine_CasaEngine_CRectangle_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::CRectangle* self = (CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
  int Left = ((int)  tolua_tonumber(tolua_S,2,0));
  int Top = ((int)  tolua_tonumber(tolua_S,3,0));
  int Width = ((int)  tolua_tonumber(tolua_S,4,0));
  int Height = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(Left,Top,Width,Height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Left of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Left00
static int tolua_CasaEngine_CasaEngine_CRectangle_Left00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Left'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Left();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Left'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Right of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Right00
static int tolua_CasaEngine_CasaEngine_CRectangle_Right00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Right'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Right();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Right'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Top of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Top00
static int tolua_CasaEngine_CasaEngine_CRectangle_Top00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Top'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Top();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Top'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Bottom of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Bottom00
static int tolua_CasaEngine_CasaEngine_CRectangle_Bottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Bottom'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Bottom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Bottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Width of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Width00
static int tolua_CasaEngine_CasaEngine_CRectangle_Width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Width'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Height of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Height00
static int tolua_CasaEngine_CasaEngine_CRectangle_Height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Height'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Size of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Size00
static int tolua_CasaEngine_CasaEngine_CRectangle_Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Size'", NULL);
#endif
  {
   CasaEngine::CVector2<int> tolua_ret = (CasaEngine::CVector2<int>)  self->Size();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CasaEngine::CVector2<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CasaEngine::CVector2<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CasaEngine::CVector2<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Intersects of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Intersects00
static int tolua_CasaEngine_CasaEngine_CRectangle_Intersects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CVector2<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CVector2<int>* Point = ((const CasaEngine::CVector2<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Intersects'", NULL);
#endif
  {
   CasaEngine::TIntersection tolua_ret = (CasaEngine::TIntersection)  self->Intersects(*Point);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Intersects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Intersects of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle_Intersects01
static int tolua_CasaEngine_CasaEngine_CRectangle_Intersects01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CRectangle* Rect = ((const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Intersects'", NULL);
#endif
  {
   CasaEngine::TIntersection tolua_ret = (CasaEngine::TIntersection)  self->Intersects(*Rect);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_CRectangle_Intersects00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CasaEngine::CRectangle */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_CRectangle__eq00
static int tolua_CasaEngine_CasaEngine_CRectangle__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::CRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CasaEngine::CRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::CRectangle* self = (const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,1,0);
  const CasaEngine::CRectangle* Rect = ((const CasaEngine::CRectangle*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*Rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  CasaEngine::LogManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_LogManager_Instance00
static int tolua_CasaEngine_CasaEngine_LogManager_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::LogManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::LogManager& tolua_ret = (CasaEngine::LogManager&)  CasaEngine::LogManager::Instance();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CasaEngine::LogManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVerbosity of class  CasaEngine::LogManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_LogManager_getVerbosity00
static int tolua_CasaEngine_CasaEngine_LogManager_getVerbosity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::LogManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::LogManager* self = (const CasaEngine::LogManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVerbosity'", NULL);
#endif
  {
   CasaEngine::TLogVerbosity tolua_ret = (CasaEngine::TLogVerbosity)  self->getVerbosity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVerbosity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVerbosity of class  CasaEngine::LogManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_LogManager_setVerbosity00
static int tolua_CasaEngine_CasaEngine_LogManager_setVerbosity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::LogManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::LogManager* self = (CasaEngine::LogManager*)  tolua_tousertype(tolua_S,1,0);
  CasaEngine::TLogVerbosity val = ((CasaEngine::TLogVerbosity) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVerbosity'", NULL);
#endif
  {
   self->setVerbosity(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVerbosity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  CasaEngine::LogManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_LogManager_Log00
static int tolua_CasaEngine_CasaEngine_LogManager_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::LogManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::LogManager* self = (CasaEngine::LogManager*)  tolua_tousertype(tolua_S,1,0);
  CasaEngine::TLogVerbosity verbose_ = ((CasaEngine::TLogVerbosity) (int)  tolua_tonumber(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'", NULL);
#endif
  {
   self->Log(verbose_,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Open of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Open00
static int tolua_CasaEngine_CasaEngine_IFile_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName_ = ((const char*)  tolua_tostring(tolua_S,2,0));
  CasaEngine::FileMode::TFileMode mode_ = ((CasaEngine::FileMode::TFileMode) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Open(fileName_,mode_);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Create00
static int tolua_CasaEngine_CasaEngine_IFile_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName_ = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool append_ = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Create(fileName_,append_);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Close00
static int tolua_CasaEngine_CasaEngine_IFile_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'", NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exists of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Exists00
static int tolua_CasaEngine_CasaEngine_IFile_Exists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Exists();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Read of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Read00
static int tolua_CasaEngine_CasaEngine_IFile_Read00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  char* dst_ = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int size_ = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Read'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Read(dst_,size_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Read'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Write of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Write00
static int tolua_CasaEngine_CasaEngine_IFile_Write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  char* data_ = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int size_ = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Write'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Write(data_,size_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Write'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Seek of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Seek00
static int tolua_CasaEngine_CasaEngine_IFile_Seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  unsigned int off_ = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  CasaEngine::SeekDir::TSeekDir dir_ = ((CasaEngine::SeekDir::TSeekDir) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Seek'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->Seek(off_,dir_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Seek of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Seek01
static int tolua_CasaEngine_CasaEngine_IFile_Seek01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
  unsigned int pos_ = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Seek'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->Seek(pos_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_IFile_Seek00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Position of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Position00
static int tolua_CasaEngine_CasaEngine_IFile_Position00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Position'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->Position();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Position'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBuffer of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_GetBuffer00
static int tolua_CasaEngine_CasaEngine_IFile_GetBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBuffer'", NULL);
#endif
  {
   char* tolua_ret = (char*)  self->GetBuffer();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBufferLength of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_GetBufferLength00
static int tolua_CasaEngine_CasaEngine_IFile_GetBufferLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::IFile* self = (CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBufferLength'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetBufferLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBufferLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Fullname of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Fullname00
static int tolua_CasaEngine_CasaEngine_IFile_Fullname00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Fullname'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->Fullname();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Fullname'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Filename of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Filename00
static int tolua_CasaEngine_CasaEngine_IFile_Filename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Filename'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->Filename();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Filename'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShortFilename of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_ShortFilename00
static int tolua_CasaEngine_CasaEngine_IFile_ShortFilename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShortFilename'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->ShortFilename();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShortFilename'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Extension of class  CasaEngine::IFile */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IFile_Extension00
static int tolua_CasaEngine_CasaEngine_IFile_Extension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::IFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::IFile* self = (const CasaEngine::IFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Extension'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->Extension();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Extension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Open of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Open00
static int tolua_CasaEngine_CasaEngine_File_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName_ = ((const char*)  tolua_tostring(tolua_S,2,0));
  CasaEngine::FileMode::TFileMode mode_ = ((CasaEngine::FileMode::TFileMode) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Open(fileName_,mode_);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Create00
static int tolua_CasaEngine_CasaEngine_File_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName_ = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool append_ = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Create(fileName_,append_);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Close00
static int tolua_CasaEngine_CasaEngine_File_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'", NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exists of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Exists00
static int tolua_CasaEngine_CasaEngine_File_Exists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::File* self = (const CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Exists();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Read of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Read00
static int tolua_CasaEngine_CasaEngine_File_Read00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
  char* dst_ = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int size_ = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Read'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Read(dst_,size_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Read'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Write of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Write00
static int tolua_CasaEngine_CasaEngine_File_Write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
  char* data_ = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int size_ = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Write'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Write(data_,size_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Write'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Seek of class  CasaEngine::File */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_File_Seek00
static int tolua_CasaEngine_CasaEngine_File_Seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::File* self = (CasaEngine::File*)  tolua_tousertype(tolua_S,1,0);
  unsigned int off_ = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  CasaEngine::SeekDir::TSeekDir dir_ = ((CasaEngine::SeekDir::TSeekDir) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Seek'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->Seek(off_,dir_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenFile of class  CasaEngine::IOManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IOManager_OpenFile00
static int tolua_CasaEngine_CasaEngine_IOManager_OpenFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::IOManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string fileName_ = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  CasaEngine::FileMode::TFileMode mode_ = ((CasaEngine::FileMode::TFileMode) (int)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::IFile* tolua_ret = (CasaEngine::IFile*)  CasaEngine::IOManager::OpenFile(fileName_,mode_);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::IFile");
   tolua_pushcppstring(tolua_S,(const char*)fileName_);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenFile of class  CasaEngine::IOManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IOManager_OpenFile01
static int tolua_CasaEngine_CasaEngine_IOManager_OpenFile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::IOManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileName_ = ((const char*)  tolua_tostring(tolua_S,2,0));
  CasaEngine::FileMode::TFileMode mode_ = ((CasaEngine::FileMode::TFileMode) (int)  tolua_tonumber(tolua_S,3,0));
  {
   CasaEngine::IFile* tolua_ret = (CasaEngine::IFile*)  CasaEngine::IOManager::OpenFile(fileName_,mode_);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::IFile");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CasaEngine_CasaEngine_IOManager_OpenFile00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateFile of class  CasaEngine::IOManager */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_IOManager_CreateFile00
static int tolua_CasaEngine_CasaEngine_IOManager_CreateFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::IOManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string filename_ = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool append_ = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   CasaEngine::IFile* tolua_ret = (CasaEngine::IFile*)  CasaEngine::IOManager::CreateFile(filename_,append_);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::IFile");
   tolua_pushcppstring(tolua_S,(const char*)filename_);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: handled of class  CasaEngine::EventArgs */
#ifndef TOLUA_DISABLE_tolua_get_CasaEngine__EventArgs_unsigned_handled
static int tolua_get_CasaEngine__EventArgs_unsigned_handled(lua_State* tolua_S)
{
  CasaEngine::EventArgs* self = (CasaEngine::EventArgs*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'handled'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->handled);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: handled of class  CasaEngine::EventArgs */
#ifndef TOLUA_DISABLE_tolua_set_CasaEngine__EventArgs_unsigned_handled
static int tolua_set_CasaEngine__EventArgs_unsigned_handled(lua_State* tolua_S)
{
  CasaEngine::EventArgs* self = (CasaEngine::EventArgs*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'handled'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->handled = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CasaEngine::EventArgs */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventArgs_new00
static int tolua_CasaEngine_CasaEngine_EventArgs_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::EventArgs",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::EventArgs* tolua_ret = (CasaEngine::EventArgs*)  Mtolua_new((CasaEngine::EventArgs)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::EventArgs");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CasaEngine::EventArgs */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventArgs_new00_local
static int tolua_CasaEngine_CasaEngine_EventArgs_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::EventArgs",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::EventArgs* tolua_ret = (CasaEngine::EventArgs*)  Mtolua_new((CasaEngine::EventArgs)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CasaEngine::EventArgs");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  CasaEngine::Event */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_Event_getName00
static int tolua_CasaEngine_CasaEngine_Event_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::Event",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::Event* self = (const CasaEngine::Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connected of class  CasaEngine::EventConnection */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventConnection_connected00
static int tolua_CasaEngine_CasaEngine_EventConnection_connected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::EventConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::EventConnection* self = (const CasaEngine::EventConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  CasaEngine::EventConnection */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventConnection_disconnect00
static int tolua_CasaEngine_CasaEngine_EventConnection_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventConnection* self = (CasaEngine::EventConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEvent of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_addEvent00
static int tolua_CasaEngine_CasaEngine_EventSet_addEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEvent'", NULL);
#endif
  {
   self->addEvent(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeEvent of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_removeEvent00
static int tolua_CasaEngine_CasaEngine_EventSet_removeEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeEvent'", NULL);
#endif
  {
   self->removeEvent(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllEvents of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_removeAllEvents00
static int tolua_CasaEngine_CasaEngine_EventSet_removeAllEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllEvents'", NULL);
#endif
  {
   self->removeAllEvents();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEventPresent of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_isEventPresent00
static int tolua_CasaEngine_CasaEngine_EventSet_isEventPresent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEventPresent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEventPresent(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEventPresent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fireEvent of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_fireEvent00
static int tolua_CasaEngine_CasaEngine_EventSet_fireEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CasaEngine::EventArgs",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  CasaEngine::EventArgs* args = ((CasaEngine::EventArgs*)  tolua_tousertype(tolua_S,3,0));
  std::string eventnamespace = ((std::string)  tolua_tocppstring(tolua_S,4,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fireEvent'", NULL);
#endif
  {
   self->fireEvent(name,*args,eventnamespace);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fireEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMuted of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_isMuted00
static int tolua_CasaEngine_CasaEngine_EventSet_isMuted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CasaEngine::EventSet* self = (const CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMuted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMuted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMuted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMutedState of class  CasaEngine::EventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_EventSet_setMutedState00
static int tolua_CasaEngine_CasaEngine_EventSet_setMutedState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CasaEngine::EventSet",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CasaEngine::EventSet* self = (CasaEngine::EventSet*)  tolua_tousertype(tolua_S,1,0);
  bool setting = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMutedState'", NULL);
#endif
  {
   self->setMutedState(setting);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMutedState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  CasaEngine::GlobalEventSet */
#ifndef TOLUA_DISABLE_tolua_CasaEngine_CasaEngine_GlobalEventSet_Instance00
static int tolua_CasaEngine_CasaEngine_GlobalEventSet_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CasaEngine::GlobalEventSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CasaEngine::GlobalEventSet& tolua_ret = (CasaEngine::GlobalEventSet&)  CasaEngine::GlobalEventSet::Instance();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CasaEngine::GlobalEventSet");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CasaEngine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"sf",0);
  tolua_beginmodule(tolua_S,"sf");
   tolua_cclass(tolua_S,"Mouse","sf::Mouse","",NULL);
   tolua_beginmodule(tolua_S,"Mouse");
    tolua_constant(tolua_S,"Left",sf::Mouse::Left);
    tolua_constant(tolua_S,"Right",sf::Mouse::Right);
    tolua_constant(tolua_S,"Middle",sf::Mouse::Middle);
    tolua_constant(tolua_S,"XButton1",sf::Mouse::XButton1);
    tolua_constant(tolua_S,"XButton2",sf::Mouse::XButton2);
    tolua_constant(tolua_S,"ButtonCount",sf::Mouse::ButtonCount);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Keyboard","sf::Keyboard","",NULL);
   tolua_beginmodule(tolua_S,"Keyboard");
    tolua_constant(tolua_S,"Unknown",sf::Keyboard::Unknown);
    tolua_constant(tolua_S,"A",sf::Keyboard::A);
    tolua_constant(tolua_S,"B",sf::Keyboard::B);
    tolua_constant(tolua_S,"C",sf::Keyboard::C);
    tolua_constant(tolua_S,"D",sf::Keyboard::D);
    tolua_constant(tolua_S,"E",sf::Keyboard::E);
    tolua_constant(tolua_S,"F",sf::Keyboard::F);
    tolua_constant(tolua_S,"G",sf::Keyboard::G);
    tolua_constant(tolua_S,"H",sf::Keyboard::H);
    tolua_constant(tolua_S,"I",sf::Keyboard::I);
    tolua_constant(tolua_S,"J",sf::Keyboard::J);
    tolua_constant(tolua_S,"K",sf::Keyboard::K);
    tolua_constant(tolua_S,"L",sf::Keyboard::L);
    tolua_constant(tolua_S,"M",sf::Keyboard::M);
    tolua_constant(tolua_S,"N",sf::Keyboard::N);
    tolua_constant(tolua_S,"O",sf::Keyboard::O);
    tolua_constant(tolua_S,"P",sf::Keyboard::P);
    tolua_constant(tolua_S,"Q",sf::Keyboard::Q);
    tolua_constant(tolua_S,"R",sf::Keyboard::R);
    tolua_constant(tolua_S,"S",sf::Keyboard::S);
    tolua_constant(tolua_S,"T",sf::Keyboard::T);
    tolua_constant(tolua_S,"U",sf::Keyboard::U);
    tolua_constant(tolua_S,"V",sf::Keyboard::V);
    tolua_constant(tolua_S,"W",sf::Keyboard::W);
    tolua_constant(tolua_S,"X",sf::Keyboard::X);
    tolua_constant(tolua_S,"Y",sf::Keyboard::Y);
    tolua_constant(tolua_S,"Z",sf::Keyboard::Z);
    tolua_constant(tolua_S,"Num0",sf::Keyboard::Num0);
    tolua_constant(tolua_S,"Num1",sf::Keyboard::Num1);
    tolua_constant(tolua_S,"Num2",sf::Keyboard::Num2);
    tolua_constant(tolua_S,"Num3",sf::Keyboard::Num3);
    tolua_constant(tolua_S,"Num4",sf::Keyboard::Num4);
    tolua_constant(tolua_S,"Num5",sf::Keyboard::Num5);
    tolua_constant(tolua_S,"Num6",sf::Keyboard::Num6);
    tolua_constant(tolua_S,"Num7",sf::Keyboard::Num7);
    tolua_constant(tolua_S,"Num8",sf::Keyboard::Num8);
    tolua_constant(tolua_S,"Num9",sf::Keyboard::Num9);
    tolua_constant(tolua_S,"Escape",sf::Keyboard::Escape);
    tolua_constant(tolua_S,"LControl",sf::Keyboard::LControl);
    tolua_constant(tolua_S,"LShift",sf::Keyboard::LShift);
    tolua_constant(tolua_S,"LAlt",sf::Keyboard::LAlt);
    tolua_constant(tolua_S,"LSystem",sf::Keyboard::LSystem);
    tolua_constant(tolua_S,"RControl",sf::Keyboard::RControl);
    tolua_constant(tolua_S,"RShift",sf::Keyboard::RShift);
    tolua_constant(tolua_S,"RAlt",sf::Keyboard::RAlt);
    tolua_constant(tolua_S,"RSystem",sf::Keyboard::RSystem);
    tolua_constant(tolua_S,"Menu",sf::Keyboard::Menu);
    tolua_constant(tolua_S,"LBracket",sf::Keyboard::LBracket);
    tolua_constant(tolua_S,"RBracket",sf::Keyboard::RBracket);
    tolua_constant(tolua_S,"SemiColon",sf::Keyboard::SemiColon);
    tolua_constant(tolua_S,"Comma",sf::Keyboard::Comma);
    tolua_constant(tolua_S,"Period",sf::Keyboard::Period);
    tolua_constant(tolua_S,"Quote",sf::Keyboard::Quote);
    tolua_constant(tolua_S,"Slash",sf::Keyboard::Slash);
    tolua_constant(tolua_S,"BackSlash",sf::Keyboard::BackSlash);
    tolua_constant(tolua_S,"Tilde",sf::Keyboard::Tilde);
    tolua_constant(tolua_S,"Equal",sf::Keyboard::Equal);
    tolua_constant(tolua_S,"Dash",sf::Keyboard::Dash);
    tolua_constant(tolua_S,"Space",sf::Keyboard::Space);
    tolua_constant(tolua_S,"Return",sf::Keyboard::Return);
    tolua_constant(tolua_S,"BackSpace",sf::Keyboard::BackSpace);
    tolua_constant(tolua_S,"Tab",sf::Keyboard::Tab);
    tolua_constant(tolua_S,"PageUp",sf::Keyboard::PageUp);
    tolua_constant(tolua_S,"PageDown",sf::Keyboard::PageDown);
    tolua_constant(tolua_S,"End",sf::Keyboard::End);
    tolua_constant(tolua_S,"Home",sf::Keyboard::Home);
    tolua_constant(tolua_S,"Insert",sf::Keyboard::Insert);
    tolua_constant(tolua_S,"Delete",sf::Keyboard::Delete);
    tolua_constant(tolua_S,"Add",sf::Keyboard::Add);
    tolua_constant(tolua_S,"Subtract",sf::Keyboard::Subtract);
    tolua_constant(tolua_S,"Multiply",sf::Keyboard::Multiply);
    tolua_constant(tolua_S,"Divide",sf::Keyboard::Divide);
    tolua_constant(tolua_S,"Left",sf::Keyboard::Left);
    tolua_constant(tolua_S,"Right",sf::Keyboard::Right);
    tolua_constant(tolua_S,"Up",sf::Keyboard::Up);
    tolua_constant(tolua_S,"Down",sf::Keyboard::Down);
    tolua_constant(tolua_S,"Numpad0",sf::Keyboard::Numpad0);
    tolua_constant(tolua_S,"Numpad1",sf::Keyboard::Numpad1);
    tolua_constant(tolua_S,"Numpad2",sf::Keyboard::Numpad2);
    tolua_constant(tolua_S,"Numpad3",sf::Keyboard::Numpad3);
    tolua_constant(tolua_S,"Numpad4",sf::Keyboard::Numpad4);
    tolua_constant(tolua_S,"Numpad5",sf::Keyboard::Numpad5);
    tolua_constant(tolua_S,"Numpad6",sf::Keyboard::Numpad6);
    tolua_constant(tolua_S,"Numpad7",sf::Keyboard::Numpad7);
    tolua_constant(tolua_S,"Numpad8",sf::Keyboard::Numpad8);
    tolua_constant(tolua_S,"Numpad9",sf::Keyboard::Numpad9);
    tolua_constant(tolua_S,"F1",sf::Keyboard::F1);
    tolua_constant(tolua_S,"F2",sf::Keyboard::F2);
    tolua_constant(tolua_S,"F3",sf::Keyboard::F3);
    tolua_constant(tolua_S,"F4",sf::Keyboard::F4);
    tolua_constant(tolua_S,"F5",sf::Keyboard::F5);
    tolua_constant(tolua_S,"F6",sf::Keyboard::F6);
    tolua_constant(tolua_S,"F7",sf::Keyboard::F7);
    tolua_constant(tolua_S,"F8",sf::Keyboard::F8);
    tolua_constant(tolua_S,"F9",sf::Keyboard::F9);
    tolua_constant(tolua_S,"F10",sf::Keyboard::F10);
    tolua_constant(tolua_S,"F11",sf::Keyboard::F11);
    tolua_constant(tolua_S,"F12",sf::Keyboard::F12);
    tolua_constant(tolua_S,"F13",sf::Keyboard::F13);
    tolua_constant(tolua_S,"F14",sf::Keyboard::F14);
    tolua_constant(tolua_S,"F15",sf::Keyboard::F15);
    tolua_constant(tolua_S,"Pause",sf::Keyboard::Pause);
    tolua_constant(tolua_S,"KeyCount",sf::Keyboard::KeyCount);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CasaEngine",0);
  tolua_beginmodule(tolua_S,"CasaEngine");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Vector2I","CasaEngine::CVector2<int>","",tolua_collect_CasaEngine__CVector2_int_);
   #else
   tolua_cclass(tolua_S,"Vector2I","CasaEngine::CVector2<int>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Vector2I");
    tolua_function(tolua_S,"Zero",tolua_CasaEngine_CasaEngine_Vector2I_Zero00);
    tolua_function(tolua_S,"One",tolua_CasaEngine_CasaEngine_Vector2I_One00);
    tolua_function(tolua_S,"UnitX",tolua_CasaEngine_CasaEngine_Vector2I_UnitX00);
    tolua_function(tolua_S,"UnitY",tolua_CasaEngine_CasaEngine_Vector2I_UnitY00);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Vector2I_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Vector2I_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Vector2I_new00_local);
    tolua_function(tolua_S,"Set",tolua_CasaEngine_CasaEngine_Vector2I_Set00);
    tolua_function(tolua_S,"getX",tolua_CasaEngine_CasaEngine_Vector2I_getX00);
    tolua_function(tolua_S,"getY",tolua_CasaEngine_CasaEngine_Vector2I_getY00);
    tolua_function(tolua_S,"IsZero",tolua_CasaEngine_CasaEngine_Vector2I_IsZero00);
    tolua_function(tolua_S,"Length",tolua_CasaEngine_CasaEngine_Vector2I_Length00);
    tolua_function(tolua_S,"LengthSquared",tolua_CasaEngine_CasaEngine_Vector2I_LengthSq00);
    tolua_function(tolua_S,"Normalize",tolua_CasaEngine_CasaEngine_Vector2I_Normalize00);
    tolua_function(tolua_S,"Dot",tolua_CasaEngine_CasaEngine_Vector2I_Dot00);
    tolua_constant(tolua_S,"clockwise",CasaEngine::CVector2<int>::clockwise);
    tolua_constant(tolua_S,"anticlockwise",CasaEngine::CVector2<int>::anticlockwise);
    tolua_function(tolua_S,"Sign",tolua_CasaEngine_CasaEngine_Vector2I_Sign00);
    tolua_function(tolua_S,"GetOrthogonal",tolua_CasaEngine_CasaEngine_Vector2I_Perp00);
    tolua_function(tolua_S,"Truncate",tolua_CasaEngine_CasaEngine_Vector2I_Truncate00);
    tolua_function(tolua_S,"Distance",tolua_CasaEngine_CasaEngine_Vector2I_Distance00);
    tolua_function(tolua_S,"DistanceSq",tolua_CasaEngine_CasaEngine_Vector2I_DistanceSq00);
    tolua_function(tolua_S,"Reflect",tolua_CasaEngine_CasaEngine_Vector2I_Reflect00);
    tolua_function(tolua_S,"GetReverse",tolua_CasaEngine_CasaEngine_Vector2I_GetReverse00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Vector2I__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Vector2I__sub00);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Vector2I__mul00);
    tolua_function(tolua_S,".div",tolua_CasaEngine_CasaEngine_Vector2I__div00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Vector2I__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Vector2F","CasaEngine::CVector2<float>","",tolua_collect_CasaEngine__CVector2_float_);
   #else
   tolua_cclass(tolua_S,"Vector2F","CasaEngine::CVector2<float>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Vector2F");
    tolua_function(tolua_S,"Zero",tolua_CasaEngine_CasaEngine_Vector2F_Zero00);
    tolua_function(tolua_S,"One",tolua_CasaEngine_CasaEngine_Vector2F_One00);
    tolua_function(tolua_S,"UnitX",tolua_CasaEngine_CasaEngine_Vector2F_UnitX00);
    tolua_function(tolua_S,"UnitY",tolua_CasaEngine_CasaEngine_Vector2F_UnitY00);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Vector2F_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Vector2F_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Vector2F_new00_local);
    tolua_function(tolua_S,"Set",tolua_CasaEngine_CasaEngine_Vector2F_Set00);
    tolua_function(tolua_S,"getX",tolua_CasaEngine_CasaEngine_Vector2F_getX00);
    tolua_function(tolua_S,"getY",tolua_CasaEngine_CasaEngine_Vector2F_getY00);
    tolua_function(tolua_S,"IsZero",tolua_CasaEngine_CasaEngine_Vector2F_IsZero00);
    tolua_function(tolua_S,"Length",tolua_CasaEngine_CasaEngine_Vector2F_Length00);
    tolua_function(tolua_S,"LengthSquared",tolua_CasaEngine_CasaEngine_Vector2F_LengthSq00);
    tolua_function(tolua_S,"Normalize",tolua_CasaEngine_CasaEngine_Vector2F_Normalize00);
    tolua_function(tolua_S,"Dot",tolua_CasaEngine_CasaEngine_Vector2F_Dot00);
    tolua_constant(tolua_S,"clockwise",CasaEngine::CVector2<float>::clockwise);
    tolua_constant(tolua_S,"anticlockwise",CasaEngine::CVector2<float>::anticlockwise);
    tolua_function(tolua_S,"Sign",tolua_CasaEngine_CasaEngine_Vector2F_Sign00);
    tolua_function(tolua_S,"GetOrthogonal",tolua_CasaEngine_CasaEngine_Vector2F_Perp00);
    tolua_function(tolua_S,"Truncate",tolua_CasaEngine_CasaEngine_Vector2F_Truncate00);
    tolua_function(tolua_S,"Distance",tolua_CasaEngine_CasaEngine_Vector2F_Distance00);
    tolua_function(tolua_S,"DistanceSq",tolua_CasaEngine_CasaEngine_Vector2F_DistanceSq00);
    tolua_function(tolua_S,"Reflect",tolua_CasaEngine_CasaEngine_Vector2F_Reflect00);
    tolua_function(tolua_S,"GetReverse",tolua_CasaEngine_CasaEngine_Vector2F_GetReverse00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Vector2F__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Vector2F__sub00);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Vector2F__mul00);
    tolua_function(tolua_S,".div",tolua_CasaEngine_CasaEngine_Vector2F__div00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Vector2F__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Vector3F","CasaEngine::CVector3<float>","",tolua_collect_CasaEngine__CVector3_float_);
   #else
   tolua_cclass(tolua_S,"Vector3F","CasaEngine::CVector3<float>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Vector3F");
    tolua_function(tolua_S,"Zero",tolua_CasaEngine_CasaEngine_Vector3F_Zero00);
    tolua_function(tolua_S,"One",tolua_CasaEngine_CasaEngine_Vector3F_One00);
    tolua_function(tolua_S,"UnitX",tolua_CasaEngine_CasaEngine_Vector3F_UnitX00);
    tolua_function(tolua_S,"UnitY",tolua_CasaEngine_CasaEngine_Vector3F_UnitY00);
    tolua_function(tolua_S,"UnitZ",tolua_CasaEngine_CasaEngine_Vector3F_UnitZ00);
    tolua_function(tolua_S,"Up",tolua_CasaEngine_CasaEngine_Vector3F_Up00);
    tolua_function(tolua_S,"Down",tolua_CasaEngine_CasaEngine_Vector3F_Down00);
    tolua_function(tolua_S,"Right",tolua_CasaEngine_CasaEngine_Vector3F_Right00);
    tolua_function(tolua_S,"Left",tolua_CasaEngine_CasaEngine_Vector3F_Left00);
    tolua_function(tolua_S,"Forward",tolua_CasaEngine_CasaEngine_Vector3F_Forward00);
    tolua_function(tolua_S,"Backward",tolua_CasaEngine_CasaEngine_Vector3F_Backward00);
    tolua_function(tolua_S,"Dot",tolua_CasaEngine_CasaEngine_Vector3F_Dot00);
    tolua_function(tolua_S,"Cross",tolua_CasaEngine_CasaEngine_Vector3F_Cross00);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Vector3F_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Vector3F_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Vector3F_new00_local);
    tolua_function(tolua_S,"Set",tolua_CasaEngine_CasaEngine_Vector3F_Set00);
    tolua_function(tolua_S,"getX",tolua_CasaEngine_CasaEngine_Vector3F_getX00);
    tolua_function(tolua_S,"getY",tolua_CasaEngine_CasaEngine_Vector3F_getY00);
    tolua_function(tolua_S,"getZ",tolua_CasaEngine_CasaEngine_Vector3F_getZ00);
    tolua_function(tolua_S,"IsZero",tolua_CasaEngine_CasaEngine_Vector3F_IsZero00);
    tolua_function(tolua_S,"Length",tolua_CasaEngine_CasaEngine_Vector3F_Length00);
    tolua_function(tolua_S,"LengthSquared",tolua_CasaEngine_CasaEngine_Vector3F_LengthSq00);
    tolua_function(tolua_S,"Normalize",tolua_CasaEngine_CasaEngine_Vector3F_Normalize00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Vector3F__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Vector3F__sub00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Vector3F__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Vector4F","CasaEngine::CVector4<float>","",tolua_collect_CasaEngine__CVector4_float_);
   #else
   tolua_cclass(tolua_S,"Vector4F","CasaEngine::CVector4<float>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Vector4F");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Vector4F_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Vector4F_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Vector4F_new00_local);
    tolua_function(tolua_S,"Set",tolua_CasaEngine_CasaEngine_Vector4F_Set00);
    tolua_function(tolua_S,"getX",tolua_CasaEngine_CasaEngine_Vector4F_getX00);
    tolua_function(tolua_S,"getY",tolua_CasaEngine_CasaEngine_Vector4F_getY00);
    tolua_function(tolua_S,"getZ",tolua_CasaEngine_CasaEngine_Vector4F_getZ00);
    tolua_function(tolua_S,"getW",tolua_CasaEngine_CasaEngine_Vector4F_getW00);
    tolua_function(tolua_S,"Length",tolua_CasaEngine_CasaEngine_Vector4F_Length00);
    tolua_function(tolua_S,"LengthSquared",tolua_CasaEngine_CasaEngine_Vector4F_LengthSq00);
    tolua_function(tolua_S,"Normalize",tolua_CasaEngine_CasaEngine_Vector4F_Normalize00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Vector4F__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Vector4F__sub00);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Vector4F__mul00);
    tolua_function(tolua_S,".div",tolua_CasaEngine_CasaEngine_Vector4F__div00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Vector4F__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Matrix3","CasaEngine::Matrix3","",tolua_collect_CasaEngine__Matrix3);
   #else
   tolua_cclass(tolua_S,"Matrix3","CasaEngine::Matrix3","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Matrix3");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Matrix3_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Matrix3_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Matrix3_new00_local);
    tolua_function(tolua_S,"Identity",tolua_CasaEngine_CasaEngine_Matrix3_Identity00);
    tolua_function(tolua_S,"Determinant",tolua_CasaEngine_CasaEngine_Matrix3_Determinant00);
    tolua_function(tolua_S,"Transpose",tolua_CasaEngine_CasaEngine_Matrix3_Transpose00);
    tolua_function(tolua_S,"Inverse",tolua_CasaEngine_CasaEngine_Matrix3_Inverse00);
    tolua_function(tolua_S,"CreateTranslation",tolua_CasaEngine_CasaEngine_Matrix3_CreateTranslation00);
    tolua_function(tolua_S,"CreateScaling",tolua_CasaEngine_CasaEngine_Matrix3_CreateScaling00);
    tolua_function(tolua_S,"CreateRotation",tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation00);
    tolua_function(tolua_S,"CreateRotation",tolua_CasaEngine_CasaEngine_Matrix3_CreateRotation01);
    tolua_function(tolua_S,"Translate",tolua_CasaEngine_CasaEngine_Matrix3_Translate00);
    tolua_function(tolua_S,"Scale",tolua_CasaEngine_CasaEngine_Matrix3_Scale00);
    tolua_function(tolua_S,"Rotate",tolua_CasaEngine_CasaEngine_Matrix3_Rotate00);
    tolua_function(tolua_S,"Rotate",tolua_CasaEngine_CasaEngine_Matrix3_Rotate01);
    tolua_function(tolua_S,"GetTranslation",tolua_CasaEngine_CasaEngine_Matrix3_GetTranslation00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix3_Transform00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix3_Transform01);
    tolua_function(tolua_S,"TransformVector2List",tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2List00);
    tolua_function(tolua_S,"TransformVector2F",tolua_CasaEngine_CasaEngine_Matrix3_TransformVector2F00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Matrix3__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Matrix3__sub00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Matrix3__add01);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Matrix3__sub01);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Matrix3__mul00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Matrix3__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Matrix4","CasaEngine::Matrix4","",tolua_collect_CasaEngine__Matrix4);
   #else
   tolua_cclass(tolua_S,"Matrix4","CasaEngine::Matrix4","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Matrix4");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Matrix4_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Matrix4_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Matrix4_new00_local);
    tolua_function(tolua_S,"Identity",tolua_CasaEngine_CasaEngine_Matrix4_Identity00);
    tolua_function(tolua_S,"Determinant",tolua_CasaEngine_CasaEngine_Matrix4_Determinant00);
    tolua_function(tolua_S,"Transpose",tolua_CasaEngine_CasaEngine_Matrix4_Transpose00);
    tolua_function(tolua_S,"Invert",tolua_CasaEngine_CasaEngine_Matrix4_Invert00);
    tolua_function(tolua_S,"SetTranslation",tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation00);
    tolua_function(tolua_S,"SetTranslation",tolua_CasaEngine_CasaEngine_Matrix4_SetTranslation01);
    tolua_function(tolua_S,"CreateTranslation",tolua_CasaEngine_CasaEngine_Matrix4_CreateTranslation00);
    tolua_function(tolua_S,"CreateScale",tolua_CasaEngine_CasaEngine_Matrix4_CreateScale00);
    tolua_function(tolua_S,"CreateRotationX",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX00);
    tolua_function(tolua_S,"CreateRotationY",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY00);
    tolua_function(tolua_S,"CreateRotationZ",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ00);
    tolua_function(tolua_S,"CreateRotationX",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationX01);
    tolua_function(tolua_S,"CreateRotationY",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationY01);
    tolua_function(tolua_S,"CreateRotationZ",tolua_CasaEngine_CasaEngine_Matrix4_CreateRotationZ01);
    tolua_function(tolua_S,"GetTranslation",tolua_CasaEngine_CasaEngine_Matrix4_GetTranslation00);
    tolua_function(tolua_S,"Transformation",tolua_CasaEngine_CasaEngine_Matrix4_Transformation00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix4_Transform00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix4_Transform01);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix4_Transform02);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Matrix4_Transform03);
    tolua_function(tolua_S,"TransformNormal",tolua_CasaEngine_CasaEngine_Matrix4_TransformNormal00);
    tolua_function(tolua_S,"OrthoOffCenter",tolua_CasaEngine_CasaEngine_Matrix4_OrthoOffCenter00);
    tolua_function(tolua_S,"PerspectiveFOV",tolua_CasaEngine_CasaEngine_Matrix4_PerspectiveFOV00);
    tolua_function(tolua_S,"LookAt",tolua_CasaEngine_CasaEngine_Matrix4_LookAt00);
    tolua_function(tolua_S,"LookAt",tolua_CasaEngine_CasaEngine_Matrix4_LookAt01);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Matrix4__add00);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Matrix4__sub00);
    tolua_function(tolua_S,".add",tolua_CasaEngine_CasaEngine_Matrix4__add01);
    tolua_function(tolua_S,".sub",tolua_CasaEngine_CasaEngine_Matrix4__sub01);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Matrix4__mul00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_Matrix4__eq00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Quaternion","CasaEngine::Quaternion","",tolua_collect_CasaEngine__Quaternion);
   #else
   tolua_cclass(tolua_S,"Quaternion","CasaEngine::Quaternion","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Quaternion");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Quaternion_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Quaternion_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Quaternion_new00_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Quaternion_new01);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Quaternion_new01_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Quaternion_new01_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_Quaternion_new02);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_Quaternion_new02_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_Quaternion_new02_local);
    tolua_function(tolua_S,"Identity",tolua_CasaEngine_CasaEngine_Quaternion_Identity00);
    tolua_function(tolua_S,"Normalize",tolua_CasaEngine_CasaEngine_Quaternion_Normalize00);
    tolua_function(tolua_S,"Conjugate",tolua_CasaEngine_CasaEngine_Quaternion_Conjugate00);
    tolua_function(tolua_S,"ToMatrix4",tolua_CasaEngine_CasaEngine_Quaternion_ToMatrix00);
    tolua_function(tolua_S,"FromMatrix",tolua_CasaEngine_CasaEngine_Quaternion_FromMatrix00);
    tolua_function(tolua_S,"FromAxisAngle",tolua_CasaEngine_CasaEngine_Quaternion_FromAxisAngle00);
    tolua_function(tolua_S,"ToAxisAngle",tolua_CasaEngine_CasaEngine_Quaternion_ToAxisAngle00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Quaternion_Transform00);
    tolua_function(tolua_S,"Transform",tolua_CasaEngine_CasaEngine_Quaternion_Transform01);
    tolua_function(tolua_S,"FromEulerAngles",tolua_CasaEngine_CasaEngine_Quaternion_FromEulerAngles00);
    tolua_function(tolua_S,".mul",tolua_CasaEngine_CasaEngine_Quaternion__mul00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CPlane","CasaEngine::CPlane","",tolua_collect_CasaEngine__CPlane);
   #else
   tolua_cclass(tolua_S,"CPlane","CasaEngine::CPlane","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CPlane");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CPlane_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CPlane_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CPlane_new00_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CPlane_new01);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CPlane_new01_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CPlane_new01_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CPlane_new02);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CPlane_new02_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CPlane_new02_local);
    tolua_function(tolua_S,"BuildFromPoints",tolua_CasaEngine_CasaEngine_CPlane_BuildFromPoints00);
    tolua_function(tolua_S,"DistanceToPoint",tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint00);
    tolua_function(tolua_S,"DistanceToPoint",tolua_CasaEngine_CasaEngine_CPlane_DistanceToPoint01);
    tolua_function(tolua_S,"IntersectLine",tolua_CasaEngine_CasaEngine_CPlane_IntersectLine00);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_CPlane__eq00);
   tolua_endmodule(tolua_S);
   tolua_constant(tolua_S,"INT_IN",CasaEngine::INT_IN);
   tolua_constant(tolua_S,"INT_OUT",CasaEngine::INT_OUT);
   tolua_constant(tolua_S,"INT_INTERSECTS",CasaEngine::INT_INTERSECTS);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CRectangle","CasaEngine::CRectangle","",tolua_collect_CasaEngine__CRectangle);
   #else
   tolua_cclass(tolua_S,"CRectangle","CasaEngine::CRectangle","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CRectangle");
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CRectangle_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CRectangle_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CRectangle_new00_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CRectangle_new01);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CRectangle_new01_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CRectangle_new01_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CRectangle_new02);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CRectangle_new02_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CRectangle_new02_local);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_CRectangle_new03);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_CRectangle_new03_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_CRectangle_new03_local);
    tolua_function(tolua_S,"Set",tolua_CasaEngine_CasaEngine_CRectangle_Set00);
    tolua_function(tolua_S,"Left",tolua_CasaEngine_CasaEngine_CRectangle_Left00);
    tolua_function(tolua_S,"Right",tolua_CasaEngine_CasaEngine_CRectangle_Right00);
    tolua_function(tolua_S,"Top",tolua_CasaEngine_CasaEngine_CRectangle_Top00);
    tolua_function(tolua_S,"Bottom",tolua_CasaEngine_CasaEngine_CRectangle_Bottom00);
    tolua_function(tolua_S,"Width",tolua_CasaEngine_CasaEngine_CRectangle_Width00);
    tolua_function(tolua_S,"Height",tolua_CasaEngine_CasaEngine_CRectangle_Height00);
    tolua_function(tolua_S,"Size",tolua_CasaEngine_CasaEngine_CRectangle_Size00);
    tolua_function(tolua_S,"Intersects",tolua_CasaEngine_CasaEngine_CRectangle_Intersects00);
    tolua_function(tolua_S,"Intersects",tolua_CasaEngine_CasaEngine_CRectangle_Intersects01);
    tolua_function(tolua_S,".eq",tolua_CasaEngine_CasaEngine_CRectangle__eq00);
   tolua_endmodule(tolua_S);
   tolua_constant(tolua_S,"Trace",CasaEngine::Trace);
   tolua_constant(tolua_S,"Debug",CasaEngine::Debug);
   tolua_constant(tolua_S,"Info",CasaEngine::Info);
   tolua_constant(tolua_S,"Warning",CasaEngine::Warning);
   tolua_constant(tolua_S,"Error",CasaEngine::Error);
   tolua_constant(tolua_S,"Fatal",CasaEngine::Fatal);
   tolua_constant(tolua_S,"None",CasaEngine::None);
   tolua_cclass(tolua_S,"LogManager","CasaEngine::LogManager","",NULL);
   tolua_beginmodule(tolua_S,"LogManager");
    tolua_function(tolua_S,"Instance",tolua_CasaEngine_CasaEngine_LogManager_Instance00);
    tolua_function(tolua_S,"getVerbosity",tolua_CasaEngine_CasaEngine_LogManager_getVerbosity00);
    tolua_function(tolua_S,"setVerbosity",tolua_CasaEngine_CasaEngine_LogManager_setVerbosity00);
    tolua_function(tolua_S,"Log",tolua_CasaEngine_CasaEngine_LogManager_Log00);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"FileMode",0);
   tolua_beginmodule(tolua_S,"FileMode");
    tolua_constant(tolua_S,"READ",CasaEngine::FileMode::READ);
    tolua_constant(tolua_S,"STREAM",CasaEngine::FileMode::STREAM);
    tolua_constant(tolua_S,"WRITE",CasaEngine::FileMode::WRITE);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"SeekDir",0);
   tolua_beginmodule(tolua_S,"SeekDir");
    tolua_constant(tolua_S,"SEEKDIR_SET",CasaEngine::SeekDir::SEEKDIR_SET);
    tolua_constant(tolua_S,"SEEKDIR_CUR",CasaEngine::SeekDir::SEEKDIR_CUR);
    tolua_constant(tolua_S,"SEEKDIR_END",CasaEngine::SeekDir::SEEKDIR_END);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"IFile","CasaEngine::IFile","",NULL);
   tolua_beginmodule(tolua_S,"IFile");
    tolua_function(tolua_S,"Open",tolua_CasaEngine_CasaEngine_IFile_Open00);
    tolua_function(tolua_S,"Create",tolua_CasaEngine_CasaEngine_IFile_Create00);
    tolua_function(tolua_S,"Close",tolua_CasaEngine_CasaEngine_IFile_Close00);
    tolua_function(tolua_S,"Exists",tolua_CasaEngine_CasaEngine_IFile_Exists00);
    tolua_function(tolua_S,"Read",tolua_CasaEngine_CasaEngine_IFile_Read00);
    tolua_function(tolua_S,"Write",tolua_CasaEngine_CasaEngine_IFile_Write00);
    tolua_function(tolua_S,"Seek",tolua_CasaEngine_CasaEngine_IFile_Seek00);
    tolua_function(tolua_S,"Seek",tolua_CasaEngine_CasaEngine_IFile_Seek01);
    tolua_function(tolua_S,"Position",tolua_CasaEngine_CasaEngine_IFile_Position00);
    tolua_function(tolua_S,"GetBuffer",tolua_CasaEngine_CasaEngine_IFile_GetBuffer00);
    tolua_function(tolua_S,"GetBufferLength",tolua_CasaEngine_CasaEngine_IFile_GetBufferLength00);
    tolua_function(tolua_S,"Fullname",tolua_CasaEngine_CasaEngine_IFile_Fullname00);
    tolua_function(tolua_S,"Filename",tolua_CasaEngine_CasaEngine_IFile_Filename00);
    tolua_function(tolua_S,"ShortFilename",tolua_CasaEngine_CasaEngine_IFile_ShortFilename00);
    tolua_function(tolua_S,"Extension",tolua_CasaEngine_CasaEngine_IFile_Extension00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"File","CasaEngine::File","CasaEngine::IFile",NULL);
   tolua_beginmodule(tolua_S,"File");
    tolua_function(tolua_S,"Open",tolua_CasaEngine_CasaEngine_File_Open00);
    tolua_function(tolua_S,"Create",tolua_CasaEngine_CasaEngine_File_Create00);
    tolua_function(tolua_S,"Close",tolua_CasaEngine_CasaEngine_File_Close00);
    tolua_function(tolua_S,"Exists",tolua_CasaEngine_CasaEngine_File_Exists00);
    tolua_function(tolua_S,"Read",tolua_CasaEngine_CasaEngine_File_Read00);
    tolua_function(tolua_S,"Write",tolua_CasaEngine_CasaEngine_File_Write00);
    tolua_function(tolua_S,"Seek",tolua_CasaEngine_CasaEngine_File_Seek00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"IOManager","CasaEngine::IOManager","",NULL);
   tolua_beginmodule(tolua_S,"IOManager");
    tolua_function(tolua_S,"OpenFile",tolua_CasaEngine_CasaEngine_IOManager_OpenFile00);
    tolua_function(tolua_S,"OpenFile",tolua_CasaEngine_CasaEngine_IOManager_OpenFile01);
    tolua_function(tolua_S,"CreateFile",tolua_CasaEngine_CasaEngine_IOManager_CreateFile00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"EventArgs","CasaEngine::EventArgs","",tolua_collect_CasaEngine__EventArgs);
   #else
   tolua_cclass(tolua_S,"EventArgs","CasaEngine::EventArgs","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"EventArgs");
    tolua_variable(tolua_S,"handled",tolua_get_CasaEngine__EventArgs_unsigned_handled,tolua_set_CasaEngine__EventArgs_unsigned_handled);
    tolua_function(tolua_S,"new",tolua_CasaEngine_CasaEngine_EventArgs_new00);
    tolua_function(tolua_S,"new_local",tolua_CasaEngine_CasaEngine_EventArgs_new00_local);
    tolua_function(tolua_S,".call",tolua_CasaEngine_CasaEngine_EventArgs_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Event","CasaEngine::Event","",NULL);
   tolua_beginmodule(tolua_S,"Event");
    tolua_function(tolua_S,"getName",tolua_CasaEngine_CasaEngine_Event_getName00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"EventConnection","CasaEngine::EventConnection","",NULL);
   tolua_beginmodule(tolua_S,"EventConnection");
    tolua_function(tolua_S,"connected",tolua_CasaEngine_CasaEngine_EventConnection_connected00);
    tolua_function(tolua_S,"disconnect",tolua_CasaEngine_CasaEngine_EventConnection_disconnect00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"EventSet","CasaEngine::EventSet","",NULL);
   tolua_beginmodule(tolua_S,"EventSet");
    tolua_function(tolua_S,"addEvent",tolua_CasaEngine_CasaEngine_EventSet_addEvent00);
    tolua_function(tolua_S,"removeEvent",tolua_CasaEngine_CasaEngine_EventSet_removeEvent00);
    tolua_function(tolua_S,"removeAllEvents",tolua_CasaEngine_CasaEngine_EventSet_removeAllEvents00);
    tolua_function(tolua_S,"isEventPresent",tolua_CasaEngine_CasaEngine_EventSet_isEventPresent00);
    tolua_function(tolua_S,"fireEvent",tolua_CasaEngine_CasaEngine_EventSet_fireEvent00);
    tolua_function(tolua_S,"isMuted",tolua_CasaEngine_CasaEngine_EventSet_isMuted00);
    tolua_function(tolua_S,"setMutedState",tolua_CasaEngine_CasaEngine_EventSet_setMutedState00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"GlobalEventSet","CasaEngine::GlobalEventSet","CasaEngine::EventSet",NULL);
   tolua_beginmodule(tolua_S,"GlobalEventSet");
    tolua_function(tolua_S,"Instance",tolua_CasaEngine_CasaEngine_GlobalEventSet_Instance00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CasaEngine (lua_State* tolua_S) {
 return tolua_CasaEngine_open(tolua_S);
};
#endif

#endif // USE_LUA_SCRIPT