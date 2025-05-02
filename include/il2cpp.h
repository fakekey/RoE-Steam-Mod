#pragma once

#define UFUNC(methodPointer) *(void **)methodPointer

#include <cstdint>

///////////////////////////////////////////////// Basic /////////////////////////////////////////////////
typedef void (*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeData {
    Il2CppMethodPointer methodPtr;
    const MethodInfo *method;
};

struct Il2CppType {
    void *data;
    unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject {
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData {
    void *rgctxDataDummy;
    const MethodInfo *method;
    const Il2CppType *type;
    Il2CppClass *klass;
};

struct Il2CppRuntimeInterfaceOffsetPair {
    Il2CppClass *interfaceType;
    int32_t offset;
};
struct Il2CppClass_1 {
    void *image;
    void *gc_desc;
    const char *name;
    const char *namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass *element_class;
    Il2CppClass *castClass;
    Il2CppClass *declaringType;
    Il2CppClass *parent;
    void *generic_class;
    void *typeMetadataHandle;
    void *interopData;
    Il2CppClass *klass;
    void *fields;
    void *events;
    void *properties;
    void *methods;
    Il2CppClass **nestedTypes;
    Il2CppClass **implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
};

struct Il2CppClass_2 {
    Il2CppClass **typeHierarchy;
    void *unity_user_data;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    size_t cctor_thread;
    void *genericContainerHandle;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClass {
    Il2CppClass_1 _1;
    void *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};

typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppArrayBounds {
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo *, void *, void **, void *);
struct MethodInfo {
    Il2CppMethodPointer methodPointer;
    Il2CppMethodPointer virtualMethodPointer;
    InvokerMethod invoker_method;
    const char *name;
    Il2CppClass *klass;
    const Il2CppType *return_type;
    const Il2CppType **parameters;
    union {
        const Il2CppRGCTXData *rgctx_data;
        const void *methodMetadataHandle;
    };
    union {
        const void *genericMethod;
        const void *genericContainerHandle;
    };
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};
///////////////////////////////////////////////// Basic /////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////////////////////////// System.String /////////////////////////////////////////////
struct __declspec(align(8)) System_String_Fields {
    int32_t _stringLength;
    uint16_t _firstChar;
};
struct System_String_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_CompareTo;
    VirtualInvokeData _5_System_Collections_IEnumerable_GetEnumerator;
    VirtualInvokeData _6_System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
    VirtualInvokeData _7_CompareTo;
    VirtualInvokeData _8_Equals;
    VirtualInvokeData _9_GetTypeCode;
    VirtualInvokeData _10_System_IConvertible_ToBoolean;
    VirtualInvokeData _11_System_IConvertible_ToChar;
    VirtualInvokeData _12_System_IConvertible_ToSByte;
    VirtualInvokeData _13_System_IConvertible_ToByte;
    VirtualInvokeData _14_System_IConvertible_ToInt16;
    VirtualInvokeData _15_System_IConvertible_ToUInt16;
    VirtualInvokeData _16_System_IConvertible_ToInt32;
    VirtualInvokeData _17_System_IConvertible_ToUInt32;
    VirtualInvokeData _18_System_IConvertible_ToInt64;
    VirtualInvokeData _19_System_IConvertible_ToUInt64;
    VirtualInvokeData _20_System_IConvertible_ToSingle;
    VirtualInvokeData _21_System_IConvertible_ToDouble;
    VirtualInvokeData _22_System_IConvertible_ToDecimal;
    VirtualInvokeData _23_System_IConvertible_ToDateTime;
    VirtualInvokeData _24_ToString;
    VirtualInvokeData _25_System_IConvertible_ToType;
    VirtualInvokeData _26_Clone;
};
struct System_String_c {
    Il2CppClass_1 _1;
    struct System_String_StaticFields *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    System_String_VTable vtable;
};
struct System_String_o {
    System_String_c *klass;
    void *monitor;
    System_String_Fields fields;
};
///////////////////////////////////////////// System.String /////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

//////////////////////////////////////// Pinkcore.Gameplay.Health ///////////////////////////////////////
struct __declspec(align(8)) Pinkcore_Gameplay_Health_Fields {
    struct Pinkcore_Gameplay_IHealthGauge_array *_gauges;
    struct Pinkcore_Gameplay_IHealthGaugeInfo_array *_gaugeInfos;
    struct System_Collections_Generic_List_IHealthLogicModifier__o *_modifiers;
};
struct Pinkcore_Gameplay_Health_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Pinkcore_Gameplay_IHealth_Damage;
    VirtualInvokeData _5_Pinkcore_Gameplay_IHealth_DirectDamage;
    VirtualInvokeData _6_Pinkcore_Gameplay_IHealth_Recover;
    VirtualInvokeData _7_Pinkcore_Gameplay_IHealth_Revive;
    VirtualInvokeData _8_Pinkcore_Gameplay_IHealth_get_HealthLogicModifiers;
    VirtualInvokeData _9_Pinkcore_Gameplay_IHealth_AddHealthLogicModifier;
    VirtualInvokeData _10_Pinkcore_Gameplay_IHealth_RemoveHealthLogicModifier;
    VirtualInvokeData _11_Pinkcore_Gameplay_IHealthInfo_get_IsDead;
    VirtualInvokeData _12_Pinkcore_Gameplay_IHealthInfo_get_CurrentHealth;
    VirtualInvokeData _13_Pinkcore_Gameplay_IHealthInfo_get_MaxHealth;
    VirtualInvokeData _14_Pinkcore_Gameplay_IHealthInfo_get_HealthGauges;
};
struct Pinkcore_Gameplay_Health_c {
    Il2CppClass_1 _1;
    void *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    Pinkcore_Gameplay_Health_VTable vtable;
};
struct Pinkcore_Gameplay_Health_o {
    Pinkcore_Gameplay_Health_c *klass;
    void *monitor;
    Pinkcore_Gameplay_Health_Fields fields;
};
//////////////////////////////////////// Pinkcore.Gameplay.Health ///////////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////////////////// Pinkcore.Gameplay.HealthChange ////////////////////////////////////
struct __declspec(align(8)) Pinkcore_Gameplay_HealthChange_Fields {
    int32_t _type;
    struct System_Collections_Generic_List_ValueTuple_int__int___o *_healthChangesReceived;
    struct System_Collections_Generic_List_ValueTuple_int__int___o *_healthChangesApplied;
    struct System_Collections_Generic_List_HealthChangeResultType__o *_healthChangeResultTypes;
};
struct Pinkcore_Gameplay_HealthChange_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Pinkcore_Gameplay_IHealthChange_get_Type;
    VirtualInvokeData _5_AddOrUpdateEntry;
    VirtualInvokeData _6_RemoveEntry;
    VirtualInvokeData _7_AddChangeResultType;
    VirtualInvokeData _8_get_HealthChangesReceived;
    VirtualInvokeData _9_get_HealthChangesApplied;
    VirtualInvokeData _10_get_HealthChangeResultTypes;
};
struct Pinkcore_Gameplay_HealthChange_c {
    Il2CppClass_1 _1;
    void *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    Pinkcore_Gameplay_HealthChange_VTable vtable;
};
struct Pinkcore_Gameplay_HealthChange_o {
    Pinkcore_Gameplay_HealthChange_c *klass;
    void *monitor;
    Pinkcore_Gameplay_HealthChange_Fields fields;
};
///////////////////////////////////// Pinkcore.Gameplay.HealthChange ////////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////////////////// Pinkcore.Gameplay.CharacterUnit ///////////////////////////////////
struct __declspec(align(8)) Pinkcore_Gameplay_CharacterUnit_Fields {
    struct System_String_o *_typeId;
    int32_t _level;
    int32_t _playerId;
    struct Pinkcore_Gameplay_IFactionManager_o *_factionManager;
    struct Pinkcore_Gameplay_IHealthInfo_o *_health;
    struct Pinkcore_Gameplay_IProgressInfo_o *_progressInfo;
    struct Pinkcore_Gameplay_IPersistentStatusInfoManager_o *_persistentStatusInfoManager;
    struct Pinkcore_Gameplay_IActionCommandProcessor_o *_actionCommandProcessor;
    struct Pinkcore_Gameplay_ISkillStatus_array *_skillStatuses;
    struct System_String_array *_tags;
    struct Pinkcore_Gameplay_IBasicAttributes_o *_currentAttributes;
    struct Pinkcore_Gameplay_ICharacterElement_o *_characterElement;
    struct Pinkcore_Gameplay_IVariableStoreInfo_o *_extensiveAttributeOps;
    struct Pinkcore_Gameplay_IVariableStoreInfo_o *_argument;
};
struct Pinkcore_Gameplay_CharacterUnit_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Pinkcore_Gameplay_ICharacterUnit_get_ActionCommandProcessor;
    VirtualInvokeData _5_GetCustomAttribute;
    VirtualInvokeData _6_GetCustomCasterAttribute;
    VirtualInvokeData _7_GetCustomCasteeAttribute;
    VirtualInvokeData _8_Pinkcore_Gameplay_ICharacterAgent_get_TypeId;
    VirtualInvokeData _9_Pinkcore_Gameplay_ICharacterAgent_get_Level;
    VirtualInvokeData _10_Pinkcore_Gameplay_ICharacterAgent_get_CharacterId;
    VirtualInvokeData _11_Pinkcore_Gameplay_ICharacterAgent_get_CharacterType;
    VirtualInvokeData _12_Pinkcore_Gameplay_ICharacterAgent_get_PlayerFaction;
    VirtualInvokeData _13_Pinkcore_Gameplay_ICharacterAgent_get_Element;
    VirtualInvokeData _14_Pinkcore_Gameplay_ICharacterAgent_get_PvpType;
    VirtualInvokeData _15_Pinkcore_Gameplay_ICharacterAgent_get_Health;
    VirtualInvokeData _16_Pinkcore_Gameplay_ICharacterAgent_get_ProgressInfo;
    VirtualInvokeData _17_Pinkcore_Gameplay_ICharacterAgent_get_PersistentStatusInfoManager;
    VirtualInvokeData _18_Pinkcore_Gameplay_ICharacterAgent_get_CurrentAttributes;
    VirtualInvokeData _19_Pinkcore_Gameplay_ICharacterAgent_get_SkillStatuses;
    VirtualInvokeData _20_Pinkcore_Gameplay_ICharacterAgent_get_Tags;
    VirtualInvokeData _21_Pinkcore_Gameplay_IVariableStoreInfo_BasicTryGet;
};
struct Pinkcore_Gameplay_CharacterUnit_c {
    Il2CppClass_1 _1;
    void *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    Pinkcore_Gameplay_CharacterUnit_VTable vtable;
};
struct Pinkcore_Gameplay_CharacterUnit_o {
    Pinkcore_Gameplay_CharacterUnit_c *klass;
    void *monitor;
    Pinkcore_Gameplay_CharacterUnit_Fields fields;
};
///////////////////////////////////// Pinkcore.Gameplay.CharacterUnit ///////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////////////////// Pinkcore.Gameplay.HealthViewInfo //////////////////////////////////
struct Optional_Option_IPersistentStatus__Fields {
    bool hasValue;
    struct Pinkcore_Gameplay_IPersistentStatus_o *value;
};
struct Optional_Option_IPersistentStatus__o {
    Optional_Option_IPersistentStatus__Fields fields;
};
struct Optional_Option_ICharacterUnit__Fields {
    bool hasValue;
    struct Pinkcore_Gameplay_ICharacterUnit_o *value;
};
struct Optional_Option_ICharacterUnit__o {
    Optional_Option_ICharacterUnit__Fields fields;
};
struct __declspec(align(8)) Pinkcore_Gameplay_HealthViewInfo_Fields {
    int32_t _healthViewInfoType;
    int32_t _healthEventSource;
    bool _isCritical;
    bool _isAttributeRestraint;
    bool _isOmitHealthPoint;
    bool _isIgnoreRecordingStatisticDataOnCaster;
    bool _isChangeToDeath;
    int32_t _totalHealthChangeReceived;
    int32_t _totalHealthChangeApplied;
    struct System_Collections_Generic_IReadOnlyList_ValueTuple_int__int___o *_healthChangeReceivedCollection;
    struct System_Collections_Generic_IReadOnlyList_ValueTuple_int__int___o *_healthChangeAppliedCollection;
    struct Optional_Option_IPersistentStatus__o _sourceStatus;
    struct Optional_Option_ICharacterUnit__o _statisticCaster;
};
struct Pinkcore_Gameplay_HealthViewInfo_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Pinkcore_Gameplay_IHealthViewInfo_get_HealthViewInfoType;
    VirtualInvokeData _5_Pinkcore_Gameplay_IHealthViewInfo_get_HealthEventSource;
    VirtualInvokeData _6_Pinkcore_Gameplay_IHealthViewInfo_get_IsCritical;
    VirtualInvokeData _7_Pinkcore_Gameplay_IHealthViewInfo_get_IsAttributeRestraint;
    VirtualInvokeData _8_Pinkcore_Gameplay_IHealthViewInfo_get_IsOmitHealthPoint;
    VirtualInvokeData _9_Pinkcore_Gameplay_IHealthViewInfo_get_IsIgnoreRecordingStatisticDataOnCaster;
    VirtualInvokeData _10_Pinkcore_Gameplay_IHealthViewInfo_get_IsChangeToDeath;
    VirtualInvokeData _11_Pinkcore_Gameplay_IHealthViewInfo_get_TotalHealthChangeReceived;
    VirtualInvokeData _12_Pinkcore_Gameplay_IHealthViewInfo_get_TotalHealthChangeApplied;
    VirtualInvokeData _13_Pinkcore_Gameplay_IHealthViewInfo_get_HealthChangeReceivedCollection;
    VirtualInvokeData _14_Pinkcore_Gameplay_IHealthViewInfo_get_HealthChangeAppliedCollection;
    VirtualInvokeData _15_Pinkcore_Gameplay_IHealthViewInfo_get_SourceStatus;
    VirtualInvokeData _16_Pinkcore_Gameplay_IHealthViewInfo_get_StatisticCaster;
    VirtualInvokeData _17_Pinkcore_Gameplay_ICharacterViewInfo_get_Type;
    VirtualInvokeData _18_Pinkcore_Gameplay_ICharacterViewInfo_Clone;
    VirtualInvokeData _19_Pinkcore_Gameplay_ICharacterViewInfo_get_IsModifyCharacterSchedule;
};
struct Pinkcore_Gameplay_HealthViewInfo_c {
    Il2CppClass_1 _1;
    void *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    Pinkcore_Gameplay_HealthViewInfo_VTable vtable;
};
struct Pinkcore_Gameplay_HealthViewInfo_o {
    Pinkcore_Gameplay_HealthViewInfo_c *klass;
    void *monitor;
    Pinkcore_Gameplay_HealthViewInfo_Fields fields;
};
///////////////////////////////////// Pinkcore.Gameplay.HealthViewInfo //////////////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////// System.Collections.Generic.List<ValueTuple<int, int>> /////////////////////////
struct __declspec(align(8)) System_Collections_Generic_List_ValueTuple_int__int___Fields {
    struct System_ValueTuple_int__int__array *_items;
    int32_t _size;
    int32_t _version;
    Il2CppObject *_syncRoot;
};
struct System_Collections_Generic_List_ValueTuple_int__int___VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_unknown;
    VirtualInvokeData _5_set_Item;
    VirtualInvokeData _6_IndexOf;
    VirtualInvokeData _7_Insert;
    VirtualInvokeData _8_unknown;
    VirtualInvokeData _9_unknown;
    VirtualInvokeData _10_System_Collections_Generic_ICollection_T__get_IsReadOnly;
    VirtualInvokeData _11_Add;
    VirtualInvokeData _12_unknown;
    VirtualInvokeData _13_Contains;
    VirtualInvokeData _14_CopyTo;
    VirtualInvokeData _15_Remove;
    VirtualInvokeData _16_System_Collections_Generic_IEnumerable_T__GetEnumerator;
    VirtualInvokeData _17_System_Collections_IEnumerable_GetEnumerator;
    VirtualInvokeData _18_System_Collections_IList_get_Item;
    VirtualInvokeData _19_System_Collections_IList_set_Item;
    VirtualInvokeData _20_System_Collections_IList_Add;
    VirtualInvokeData _21_System_Collections_IList_Contains;
    VirtualInvokeData _22_Clear;
    VirtualInvokeData _23_System_Collections_IList_get_IsReadOnly;
    VirtualInvokeData _24_System_Collections_IList_get_IsFixedSize;
    VirtualInvokeData _25_System_Collections_IList_IndexOf;
    VirtualInvokeData _26_System_Collections_IList_Insert;
    VirtualInvokeData _27_System_Collections_IList_Remove;
    VirtualInvokeData _28_RemoveAt;
    VirtualInvokeData _29_System_Collections_ICollection_CopyTo;
    VirtualInvokeData _30_unknown;
    VirtualInvokeData _31_System_Collections_ICollection_get_SyncRoot;
    VirtualInvokeData _32_System_Collections_ICollection_get_IsSynchronized;
    VirtualInvokeData _33_get_Item;
    VirtualInvokeData _34_get_Count;
};
struct System_Collections_Generic_List_ValueTuple_int__int___c {
    Il2CppClass_1 _1;
    struct System_Collections_Generic_List_ValueTuple_int__int___StaticFields *static_fields;
    Il2CppRGCTXData *rgctx_data;
    Il2CppClass_2 _2;
    System_Collections_Generic_List_ValueTuple_int__int___VTable vtable;
};
struct System_Collections_Generic_List_ValueTuple_int__int___o {
    System_Collections_Generic_List_ValueTuple_int__int___c *klass;
    void *monitor;
    System_Collections_Generic_List_ValueTuple_int__int___Fields fields;
};
///////////////////////// System.Collections.Generic.List<ValueTuple<int, int>> /////////////////////////

//-----------------------------------------------------------------------------------------------------//

///////////////////////////////////// System.ValueTuple<int, int>[] /////////////////////////////////////
struct System_ValueTuple_int__int__Fields {
    int32_t Item1;
    int32_t Item2;
};
struct System_ValueTuple_int__int__o {
    System_ValueTuple_int__int__Fields fields;
};
struct System_ValueTuple_int__int__array {
    Il2CppObject obj;
    Il2CppArrayBounds *bounds;
    il2cpp_array_size_t max_length;
    System_ValueTuple_int__int__o m_Items[65535];
};
///////////////////////////////////// System.ValueTuple<int, int>[] /////////////////////////////////////