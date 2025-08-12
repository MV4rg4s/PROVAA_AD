//
// Generated file, do not edit! Created by opp_msgtool 6.2 from src/Mensagem.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Mensagem_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(Mensagem)

Mensagem::Mensagem(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Mensagem::Mensagem(const Mensagem& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Mensagem::~Mensagem()
{
    delete [] this->destinos;
    delete [] this->custos;
}

Mensagem& Mensagem::operator=(const Mensagem& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Mensagem::copy(const Mensagem& other)
{
    this->idNoOrigem = other.idNoOrigem;
    delete [] this->destinos;
    this->destinos = (other.destinos_arraysize==0) ? nullptr : new int[other.destinos_arraysize];
    destinos_arraysize = other.destinos_arraysize;
    for (size_t i = 0; i < destinos_arraysize; i++) {
        this->destinos[i] = other.destinos[i];
    }
    delete [] this->custos;
    this->custos = (other.custos_arraysize==0) ? nullptr : new double[other.custos_arraysize];
    custos_arraysize = other.custos_arraysize;
    for (size_t i = 0; i < custos_arraysize; i++) {
        this->custos[i] = other.custos[i];
    }
}

void Mensagem::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->idNoOrigem);
    b->pack(destinos_arraysize);
    doParsimArrayPacking(b,this->destinos,destinos_arraysize);
    b->pack(custos_arraysize);
    doParsimArrayPacking(b,this->custos,custos_arraysize);
}

void Mensagem::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->idNoOrigem);
    delete [] this->destinos;
    b->unpack(destinos_arraysize);
    if (destinos_arraysize == 0) {
        this->destinos = nullptr;
    } else {
        this->destinos = new int[destinos_arraysize];
        doParsimArrayUnpacking(b,this->destinos,destinos_arraysize);
    }
    delete [] this->custos;
    b->unpack(custos_arraysize);
    if (custos_arraysize == 0) {
        this->custos = nullptr;
    } else {
        this->custos = new double[custos_arraysize];
        doParsimArrayUnpacking(b,this->custos,custos_arraysize);
    }
}

int Mensagem::getIdNoOrigem() const
{
    return this->idNoOrigem;
}

void Mensagem::setIdNoOrigem(int idNoOrigem)
{
    this->idNoOrigem = idNoOrigem;
}

size_t Mensagem::getDestinosArraySize() const
{
    return destinos_arraysize;
}

int Mensagem::getDestinos(size_t k) const
{
    if (k >= destinos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinos_arraysize, (unsigned long)k);
    return this->destinos[k];
}

void Mensagem::setDestinosArraySize(size_t newSize)
{
    int *destinos2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = destinos_arraysize < newSize ? destinos_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        destinos2[i] = this->destinos[i];
    for (size_t i = minSize; i < newSize; i++)
        destinos2[i] = 0;
    delete [] this->destinos;
    this->destinos = destinos2;
    destinos_arraysize = newSize;
}

void Mensagem::setDestinos(size_t k, int destinos)
{
    if (k >= destinos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinos_arraysize, (unsigned long)k);
    this->destinos[k] = destinos;
}

void Mensagem::insertDestinos(size_t k, int destinos)
{
    if (k > destinos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinos_arraysize, (unsigned long)k);
    size_t newSize = destinos_arraysize + 1;
    int *destinos2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        destinos2[i] = this->destinos[i];
    destinos2[k] = destinos;
    for (i = k + 1; i < newSize; i++)
        destinos2[i] = this->destinos[i-1];
    delete [] this->destinos;
    this->destinos = destinos2;
    destinos_arraysize = newSize;
}

void Mensagem::appendDestinos(int destinos)
{
    insertDestinos(destinos_arraysize, destinos);
}

void Mensagem::eraseDestinos(size_t k)
{
    if (k >= destinos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinos_arraysize, (unsigned long)k);
    size_t newSize = destinos_arraysize - 1;
    int *destinos2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        destinos2[i] = this->destinos[i];
    for (i = k; i < newSize; i++)
        destinos2[i] = this->destinos[i+1];
    delete [] this->destinos;
    this->destinos = destinos2;
    destinos_arraysize = newSize;
}

size_t Mensagem::getCustosArraySize() const
{
    return custos_arraysize;
}

double Mensagem::getCustos(size_t k) const
{
    if (k >= custos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)custos_arraysize, (unsigned long)k);
    return this->custos[k];
}

void Mensagem::setCustosArraySize(size_t newSize)
{
    double *custos2 = (newSize==0) ? nullptr : new double[newSize];
    size_t minSize = custos_arraysize < newSize ? custos_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        custos2[i] = this->custos[i];
    for (size_t i = minSize; i < newSize; i++)
        custos2[i] = 0;
    delete [] this->custos;
    this->custos = custos2;
    custos_arraysize = newSize;
}

void Mensagem::setCustos(size_t k, double custos)
{
    if (k >= custos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)custos_arraysize, (unsigned long)k);
    this->custos[k] = custos;
}

void Mensagem::insertCustos(size_t k, double custos)
{
    if (k > custos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)custos_arraysize, (unsigned long)k);
    size_t newSize = custos_arraysize + 1;
    double *custos2 = new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        custos2[i] = this->custos[i];
    custos2[k] = custos;
    for (i = k + 1; i < newSize; i++)
        custos2[i] = this->custos[i-1];
    delete [] this->custos;
    this->custos = custos2;
    custos_arraysize = newSize;
}

void Mensagem::appendCustos(double custos)
{
    insertCustos(custos_arraysize, custos);
}

void Mensagem::eraseCustos(size_t k)
{
    if (k >= custos_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)custos_arraysize, (unsigned long)k);
    size_t newSize = custos_arraysize - 1;
    double *custos2 = (newSize == 0) ? nullptr : new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        custos2[i] = this->custos[i];
    for (i = k; i < newSize; i++)
        custos2[i] = this->custos[i+1];
    delete [] this->custos;
    this->custos = custos2;
    custos_arraysize = newSize;
}

class MensagemDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_idNoOrigem,
        FIELD_destinos,
        FIELD_custos,
    };
  public:
    MensagemDescriptor();
    virtual ~MensagemDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(MensagemDescriptor)

MensagemDescriptor::MensagemDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Mensagem)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

MensagemDescriptor::~MensagemDescriptor()
{
    delete[] propertyNames;
}

bool MensagemDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Mensagem *>(obj)!=nullptr;
}

const char **MensagemDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MensagemDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MensagemDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int MensagemDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_idNoOrigem
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_destinos
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_custos
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *MensagemDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "idNoOrigem",
        "destinos",
        "custos",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int MensagemDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "idNoOrigem") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destinos") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "custos") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *MensagemDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_idNoOrigem
        "int",    // FIELD_destinos
        "double",    // FIELD_custos
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **MensagemDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MensagemDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MensagemDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_destinos: return pp->getDestinosArraySize();
        case FIELD_custos: return pp->getCustosArraySize();
        default: return 0;
    }
}

void MensagemDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_destinos: pp->setDestinosArraySize(size); break;
        case FIELD_custos: pp->setCustosArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Mensagem'", field);
    }
}

const char *MensagemDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MensagemDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_idNoOrigem: return long2string(pp->getIdNoOrigem());
        case FIELD_destinos: return long2string(pp->getDestinos(i));
        case FIELD_custos: return double2string(pp->getCustos(i));
        default: return "";
    }
}

void MensagemDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_idNoOrigem: pp->setIdNoOrigem(string2long(value)); break;
        case FIELD_destinos: pp->setDestinos(i,string2long(value)); break;
        case FIELD_custos: pp->setCustos(i,string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mensagem'", field);
    }
}

omnetpp::cValue MensagemDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_idNoOrigem: return pp->getIdNoOrigem();
        case FIELD_destinos: return pp->getDestinos(i);
        case FIELD_custos: return pp->getCustos(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Mensagem' as cValue -- field index out of range?", field);
    }
}

void MensagemDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        case FIELD_idNoOrigem: pp->setIdNoOrigem(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destinos: pp->setDestinos(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_custos: pp->setCustos(i,value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mensagem'", field);
    }
}

const char *MensagemDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr MensagemDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MensagemDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Mensagem *pp = omnetpp::fromAnyPtr<Mensagem>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mensagem'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

