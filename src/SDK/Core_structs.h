#ifdef _MSC_VER
	#pragma pack ( push, 0x4 )
#endif

/*
# ========================================================================================= #
# Script Structs
# ========================================================================================= #
*/

// ScriptStruct Core.Object.Rotator
// 0x000C
struct FRotator
{
	int Pitch, Yaw, Roll;

	FRotator() {}

	FRotator(int Pitch, int Yaw, int Roll)
	{
		this->Pitch = Pitch;
		this->Yaw = Yaw;
		this->Roll = Roll;
	}

	FRotator operator - () { return FRotator(-Pitch, -Yaw, -Roll); }

	FRotator operator + (FRotator r) { return FRotator(Pitch + r.Pitch, Yaw + r.Yaw, Roll + r.Roll); }
	FRotator operator - (FRotator r) { return FRotator(Pitch - r.Pitch, Yaw - r.Yaw, Roll - r.Roll); }
	FRotator operator * (FRotator r) { return FRotator(Pitch * r.Pitch, Yaw * r.Yaw, Roll * r.Roll); }
	FRotator operator / (FRotator r) { return FRotator(Pitch / r.Pitch, Yaw / r.Yaw, Roll / r.Roll); }

	FRotator operator = (FRotator r)
	{
		this->Pitch = r.Pitch;
		this->Yaw = r.Yaw;
		this->Roll = r.Roll;

		return *this;
	}

	FRotator operator += (FRotator r)
	{
		this->Pitch += r.Pitch;
		this->Yaw += r.Yaw;
		this->Roll += r.Roll;

		return *this;
	}

	FRotator operator -= (FRotator r)
	{
		this->Pitch -= r.Pitch;
		this->Yaw -= r.Yaw;
		this->Roll -= r.Roll;

		return *this;
	}

	FRotator operator /= (FRotator r)
	{
		this->Pitch /= r.Pitch;
		this->Yaw /= r.Yaw;
		this->Roll /= r.Roll;

		return *this;
	}

	FRotator operator *= (FRotator r)
	{
		this->Pitch *= r.Pitch;
		this->Yaw *= r.Yaw;
		this->Roll *= r.Roll;

		return *this;
	}

	FRotator operator + (FLOAT f) { return FRotator(Pitch + f, Yaw + f, Roll + f); }
	FRotator operator - (FLOAT f) { return FRotator(Pitch - f, Yaw - f, Roll - f); }
	FRotator operator * (FLOAT f) { return FRotator(Pitch * f, Yaw * f, Roll * f); }
	FRotator operator / (FLOAT f) { return FRotator(Pitch / f, Yaw / f, Roll / f); }

	FRotator operator = (FLOAT f)
	{
		this->Pitch = f;
		this->Yaw = f;
		this->Roll = f;

		return *this;
	}

	FRotator operator += (FLOAT f)
	{
		this->Pitch += f;
		this->Yaw += f;
		this->Roll += f;

		return *this;
	}

	FRotator operator -= (FLOAT f)
	{
		this->Pitch -= f;
		this->Yaw -= f;
		this->Roll -= f;

		return *this;
	}

	FRotator operator /= (FLOAT f)
	{
		this->Pitch /= f;
		this->Yaw /= f;
		this->Roll /= f;

		return *this;
	}

	FRotator operator *= (FLOAT f)
	{
		this->Pitch *= f;
		this->Yaw *= f;
		this->Roll *= f;

		return *this;
	}

	BOOL operator == (FRotator r) { return ((Pitch == r.Pitch) && (Yaw == r.Yaw) && (Roll == r.Roll)); }
	BOOL operator != (FRotator r) { return ((Pitch != r.Pitch) || (Yaw != r.Yaw) || (Roll != r.Roll)); }

	FLOAT operator [] (INT i)
	{
		if (i == 0)
			return Pitch;
		else if (i == 1)
			return Yaw;
		else
			return Roll;
	}
};

// ScriptStruct Core.Object.Vector
// 0x000C
struct FVector
{
	float X, Y, Z;

	FVector() {}

	FVector(float X, float Y, float Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	FVector operator - () { return FVector(-X, -Y, -Z); }

	FVector operator + (FVector v) { return FVector(X + v.X, Y + v.Y, Z + v.Z); }
	FVector operator - (FVector v) { return FVector(X - v.X, Y - v.Y, Z - v.Z); }
	FVector operator * (FVector v) { return FVector(X * v.X, Y * v.Y, Z * v.Z); }
	FVector operator / (FVector v) { return FVector(X / v.X, Y / v.Y, Z / v.Z); }

	FVector operator = (FVector v)
	{
		this->X = v.X;
		this->Y = v.Y;
		this->Z = v.Z;

		return *this;
	}

	FVector operator += (FVector v)
	{
		this->X += v.X;
		this->Y += v.Y;
		this->Z += v.Z;

		return *this;
	}

	FVector operator -= (FVector v)
	{
		this->X -= v.X;
		this->Y -= v.Y;
		this->Z -= v.Z;

		return *this;
	}

	FVector operator /= (FVector v)
	{
		this->X /= v.X;
		this->Y /= v.Y;
		this->Z /= v.Z;

		return *this;
	}

	FVector operator *= (FVector v)
	{
		this->X *= v.X;
		this->Y *= v.Y;
		this->Z *= v.Z;

		return *this;
	}

	FVector operator + (FLOAT f) { return FVector(X + f, Y + f, Z + f); }
	FVector operator - (FLOAT f) { return FVector(X - f, Y - f, Z - f); }
	FVector operator * (FLOAT f) { return FVector(X * f, Y * f, Z * f); }
	FVector operator / (FLOAT f) { return FVector(X / f, Y / f, Z / f); }

	FVector operator = (FLOAT f)
	{
		this->X = f;
		this->Y = f;
		this->Z = f;

		return *this;
	}

	FVector operator += (FLOAT f)
	{
		this->X += f;
		this->Y += f;
		this->Z += f;

		return *this;
	}

	FVector operator -= (FLOAT f)
	{
		this->X -= f;
		this->Y -= f;
		this->Z -= f;

		return *this;
	}

	FVector operator /= (FLOAT f)
	{
		this->X /= f;
		this->Y /= f;
		this->Z /= f;

		return *this;
	}

	FVector operator *= (FLOAT f)
	{
		this->X *= f;
		this->Y *= f;
		this->Z *= f;

		return *this;
	}

	BOOL operator == (FVector v) { return ((X == v.X) && (Y == v.Y) && (Z == v.Z)); }
	BOOL operator != (FVector v) { return ((X != v.X) || (Y != v.Y) || (Z != v.Z)); }

	FLOAT operator [] (INT i)
	{
		if (i == 0)
			return X;
		else if (i == 1)
			return Y;
		else
			return Z;
	}

	FLOAT Length() { return sqrtf(X * X + Y * Y + Z * Z); }
	FRotator Rotator();
};

// ScriptStruct Core.Object.Plane
// 0x0004(0x0010 - 0x000C)
struct FPlane : FVector
{
	float                                              W;                                                		// 0x000C (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Guid
// 0x0010
struct FGuid
{
	int                                                A;                                                		// 0x0000 (0x0004) [0x0000000000000000]              
	int                                                B;                                                		// 0x0004 (0x0004) [0x0000000000000000]              
	int                                                C;                                                		// 0x0008 (0x0004) [0x0000000000000000]              
	int                                                D;                                                		// 0x000C (0x0004) [0x0000000000000000]              
};

// ScriptStruct Core.Object.Vector2D
// 0x0008
struct FVector2D
{
	float                                              X;                                                		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              Y;                                                		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Vector4
// 0x0010
struct FVector4
{
	float                                              X;                                                		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              Y;                                                		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              Z;                                                		// 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              W;                                                		// 0x000C (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.LinearColor
// 0x0010
struct FLinearColor
{
	float                                              R;                                                		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              G;                                                		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              B;                                                		// 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              A;                                                		// 0x000C (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Color
// 0x0004
struct FColor
{
	unsigned char                                      B;                                                		// 0x0000 (0x0001) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      G;                                                		// 0x0001 (0x0001) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      R;                                                		// 0x0002 (0x0001) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      A;                                                		// 0x0003 (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Quat
// 0x0010
struct FQuat
{
	float                                              X;                                                		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              Y;                                                		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              Z;                                                		// 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              W;                                                		// 0x000C (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Matrix
// 0x0040
struct FMatrix
{
	struct FPlane                                      XPlane;                                           		// 0x0000 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	struct FPlane                                      YPlane;                                           		// 0x0010 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	struct FPlane                                      ZPlane;                                           		// 0x0020 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	struct FPlane                                      WPlane;                                           		// 0x0030 (0x0010) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.BoxSphereBounds
// 0x001C
struct FBoxSphereBounds
{
	struct FVector                                     Origin;                                           		// 0x0000 (0x000C) [0x0000000000000000]              
	struct FVector                                     BoxExtent;                                        		// 0x000C (0x000C) [0x0000000000000000]              
	float                                              SphereRadius;                                     		// 0x0018 (0x0004) [0x0000000000000000]              
};

// ScriptStruct Core.Object.TwoVectors
// 0x0018
struct FTwoVectors
{
	struct FVector                                     v1;                                               		// 0x0000 (0x000C) [0x0000000000000001]              ( CPF_Edit )
	struct FVector                                     v2;                                               		// 0x000C (0x000C) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.Pointer
// 0x0004
struct FPointer
{
	int                                                Dummy;                                            		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.OctreeElementId
// 0x0008
struct FOctreeElementId
{
	struct FPointer                                    Node;                                             		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                ElementIndex;                                     		// 0x0004 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.RenderCommandFence
// 0x0004
struct FRenderCommandFence
{
	int                                                NumPendingFences;                                 		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.RawDistribution
// 0x0018
struct FRawDistribution
{
	unsigned char                                      Type;                                             		// 0x0000 (0x0001) [0x0000000000000000]              
	unsigned char                                      Op;                                               		// 0x0001 (0x0001) [0x0000000000000000]              
	unsigned char                                      LookupTableNumElements;                           		// 0x0002 (0x0001) [0x0000000000000000]              
	unsigned char                                      LookupTableChunkSize;                             		// 0x0003 (0x0001) [0x0000000000000000]              
	TArray< float >                                    LookupTable;                                      		// 0x0004 (0x000C) [0x0000000000400000]              ( CPF_NeedCtorLink )
	float                                              LookupTableTimeScale;                             		// 0x0010 (0x0004) [0x0000000000000000]              
	float                                              LookupTableStartTime;                             		// 0x0014 (0x0004) [0x0000000000000000]              
};

// ScriptStruct Core.Object.InterpCurvePointQuat
// 0x0035
struct FInterpCurvePointQuat
{
	float                                              InVal;                                            		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	struct FQuat                                       OutVal;                                           		// 0x0004 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	struct FQuat                                       ArriveTangent;                                    		// 0x0014 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	struct FQuat                                       LeaveTangent;                                     		// 0x0024 (0x0010) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      InterpMode;                                       		// 0x0034 (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.InterpCurveQuat
// 0x000D
struct FInterpCurveQuat
{
	TArray< struct FInterpCurvePointQuat >             Points;                                           		// 0x0000 (0x000C) [0x0000000000400001]              ( CPF_Edit | CPF_NeedCtorLink )
	unsigned char                                      InterpMethod;                                     		// 0x000C (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.InterpCurvePointTwoVectors
// 0x004D
struct FInterpCurvePointTwoVectors
{
	float                                              InVal;                                            		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	struct FTwoVectors                                 OutVal;                                           		// 0x0004 (0x0018) [0x0000000000000001]              ( CPF_Edit )
	struct FTwoVectors                                 ArriveTangent;                                    		// 0x001C (0x0018) [0x0000000000000001]              ( CPF_Edit )
	struct FTwoVectors                                 LeaveTangent;                                     		// 0x0034 (0x0018) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      InterpMode;                                       		// 0x004C (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.InterpCurveTwoVectors
// 0x000D
struct FInterpCurveTwoVectors
{
	TArray< struct FInterpCurvePointTwoVectors >       Points;                                           		// 0x0000 (0x000C) [0x0000000000400001]              ( CPF_Edit | CPF_NeedCtorLink )
	unsigned char                                      InterpMethod;                                     		// 0x000C (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.Cylinder
// 0x0008
struct FCylinder
{
	float                                              Radius;                                           		// 0x0000 (0x0004) [0x0000000000000000]              
	float                                              Height;                                           		// 0x0004 (0x0004) [0x0000000000000000]              
};

// ScriptStruct Core.Object.InterpCurvePointVector
// 0x0029
struct FInterpCurvePointVector
{
	float                                              InVal;                                            		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	struct FVector                                     OutVal;                                           		// 0x0004 (0x000C) [0x0000000000000001]              ( CPF_Edit )
	struct FVector                                     ArriveTangent;                                    		// 0x0010 (0x000C) [0x0000000000000001]              ( CPF_Edit )
	struct FVector                                     LeaveTangent;                                     		// 0x001C (0x000C) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      InterpMode;                                       		// 0x0028 (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.InterpCurveVector
// 0x000D
struct FInterpCurveVector
{
	TArray< struct FInterpCurvePointVector >           Points;                                           		// 0x0000 (0x000C) [0x0000000000400001]              ( CPF_Edit | CPF_NeedCtorLink )
	unsigned char                                      InterpMethod;                                     		// 0x000C (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.InterpCurvePointVector2D
// 0x001D
struct FInterpCurvePointVector2D
{
	float                                              InVal;                                            		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	struct FVector2D                                   OutVal;                                           		// 0x0004 (0x0008) [0x0000000000000001]              ( CPF_Edit )
	struct FVector2D                                   ArriveTangent;                                    		// 0x000C (0x0008) [0x0000000000000001]              ( CPF_Edit )
	struct FVector2D                                   LeaveTangent;                                     		// 0x0014 (0x0008) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      InterpMode;                                       		// 0x001C (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.InterpCurveVector2D
// 0x000D
struct FInterpCurveVector2D
{
	TArray< struct FInterpCurvePointVector2D >         Points;                                           		// 0x0000 (0x000C) [0x0000000000400001]              ( CPF_Edit | CPF_NeedCtorLink )
	unsigned char                                      InterpMethod;                                     		// 0x000C (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.InterpCurvePointFloat
// 0x0011
struct FInterpCurvePointFloat
{
	float                                              InVal;                                            		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              OutVal;                                           		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              ArriveTangent;                                    		// 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	float                                              LeaveTangent;                                     		// 0x000C (0x0004) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      InterpMode;                                       		// 0x0010 (0x0001) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.InterpCurveFloat
// 0x000D
struct FInterpCurveFloat
{
	TArray< struct FInterpCurvePointFloat >            Points;                                           		// 0x0000 (0x000C) [0x0000000000400001]              ( CPF_Edit | CPF_NeedCtorLink )
	unsigned char                                      InterpMethod;                                     		// 0x000C (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.Box
// 0x0019
struct FBox
{
	struct FVector                                     Min;                                              		// 0x0000 (0x000C) [0x0000000000000001]              ( CPF_Edit )
	struct FVector                                     Max;                                              		// 0x000C (0x000C) [0x0000000000000001]              ( CPF_Edit )
	unsigned char                                      IsValid;                                          		// 0x0018 (0x0001) [0x0000000000000000]              
};

// ScriptStruct Core.Object.TPOV
// 0x001C
struct FTPOV
{
	struct FVector                                     Location;                                         		// 0x0000 (0x000C) [0x0000000000000001]              ( CPF_Edit )
	struct FRotator                                    Rotation;                                         		// 0x000C (0x000C) [0x0000000000000001]              ( CPF_Edit )
	float                                              FOV;                                              		// 0x0018 (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.SHVector
// 0x0030
struct FSHVector
{
	float                                              V[ 0x9 ];                                         		// 0x0000 (0x0024) [0x0000000000000001]              ( CPF_Edit )
	float                                              Padding[ 0x3 ];                                   		// 0x0024 (0x000C) [0x0000000000000000]              
};

// ScriptStruct Core.Object.SHVectorRGB
// 0x0090
struct FSHVectorRGB
{
	struct FSHVector                                   R;                                                		// 0x0000 (0x0030) [0x0000000000000001]              ( CPF_Edit )
	struct FSHVector                                   G;                                                		// 0x0030 (0x0030) [0x0000000000000001]              ( CPF_Edit )
	struct FSHVector                                   B;                                                		// 0x0060 (0x0030) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.IntPoint
// 0x0008
struct FIntPoint
{
	int                                                X;                                                		// 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
	int                                                Y;                                                		// 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
};

// ScriptStruct Core.Object.IndirectArray_Mirror
// 0x000C
struct FIndirectArray_Mirror
{
	struct FPointer                                    Data;                                             		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                ArrayNum;                                         		// 0x0004 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                ArrayMax;                                         		// 0x0008 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.RenderCommandFence_Mirror
// 0x0004
struct FRenderCommandFence_Mirror
{
	int                                                NumPendingFences;                                 		// 0x0000 (0x0004) [0x0000000000003002]              ( CPF_Const | CPF_Native | CPF_Transient )
};

// ScriptStruct Core.Object.UntypedBulkData_Mirror
// 0x0030
struct FUntypedBulkData_Mirror
{
	struct FPointer                                    VfTable;                                          		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                BulkDataFlags;                                    		// 0x0004 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                ElementCount;                                     		// 0x0008 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                BulkDataOffsetInFile;                             		// 0x000C (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                BulkDataSizeOnDisk;                               		// 0x0010 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                SavedBulkDataFlags;                               		// 0x0014 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                SavedElementCount;                                		// 0x0018 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                SavedBulkDataOffsetInFile;                        		// 0x001C (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                SavedBulkDataSizeOnDisk;                          		// 0x0020 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	struct FPointer                                    BulkData;                                         		// 0x0024 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                LockStatus;                                       		// 0x0028 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	struct FPointer                                    AttachedAr;                                       		// 0x002C (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.TextureMipBulkData_Mirror
// 0x0004(0x0034 - 0x0030)
struct FTextureMipBulkData_Mirror : FUntypedBulkData_Mirror
{
	int                                                bShouldFreeOnEmtpy;                               		// 0x0030 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.BitArray_Mirror
// 0x001C
struct FBitArray_Mirror
{
	struct FPointer                                    IndirectData;                                     		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                InlineData[ 0x4 ];                                		// 0x0004 (0x0010) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                NumBits;                                          		// 0x0014 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                MaxBits;                                          		// 0x0018 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.SparseArray_Mirror
// 0x0030
struct FSparseArray_Mirror
{
	TArray< int >                                      Elements;                                         		// 0x0000 (0x000C) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	struct FBitArray_Mirror                            AllocationFlags;                                  		// 0x000C (0x001C) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                FirstFreeIndex;                                   		// 0x0028 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                NumFreeIndices;                                   		// 0x002C (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.Set_Mirror
// 0x003C
struct FSet_Mirror
{
	struct FSparseArray_Mirror                         Elements;                                         		// 0x0000 (0x0030) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	struct FPointer                                    Hash;                                             		// 0x0030 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                InlineHash;                                       		// 0x0034 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                HashSize;                                         		// 0x0038 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.MultiMap_Mirror
// 0x003C
struct FMultiMap_Mirror
{
	struct FSet_Mirror                                 Pairs;                                            		// 0x0000 (0x003C) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.LookupMap_Mirror
// 0x000C(0x0048 - 0x003C)
struct FLookupMap_Mirror : FMultiMap_Mirror
{
	TArray< int >                                      UniqueElements;                                   		// 0x003C (0x000C) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.Map_Mirror
// 0x003C
struct FMap_Mirror
{
	struct FSet_Mirror                                 Pairs;                                            		// 0x0000 (0x003C) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.ThreadSafeCounter
// 0x0004
struct FThreadSafeCounter
{
	int                                                Value;                                            		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.Double
// 0x0008
struct FDouble
{
	int                                                A;                                                		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                B;                                                		// 0x0004 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.Object.QWord
// 0x0008
struct FQWord
{
	int                                                A;                                                		// 0x0000 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
	int                                                B;                                                		// 0x0004 (0x0004) [0x0000000000001002]              ( CPF_Const | CPF_Native )
};

// ScriptStruct Core.DistributionFloat.RawDistributionFloat
// 0x0004(0x001C - 0x0018)
struct FRawDistributionFloat : FRawDistribution
{
	class UDistributionFloat*                          Distribution;                                     		// 0x0018 (0x0004) [0x0000000006080009]              ( CPF_Edit | CPF_ExportObject | CPF_Component | CPF_NoClear | CPF_EditInline )
};

// ScriptStruct Core.DistributionVector.RawDistributionVector
// 0x0004(0x001C - 0x0018)
struct FRawDistributionVector : FRawDistribution
{
	class UDistributionVector*                         Distribution;                                     		// 0x0018 (0x0004) [0x0000000004080009]              ( CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline )
};


#ifdef _MSC_VER
	#pragma pack ( pop )
#endif