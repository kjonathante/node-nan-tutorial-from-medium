#include "Vector.h"

Nan::Persistent<v8::FunctionTemplate> Vector::constructor;

NAN_MODULE_INIT(Vector::Init) {
  /* original code */
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Vector::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Vector").ToLocalChecked());

  // link our getters and setter to the object property
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);

  Nan::SetPrototypeMethod(ctor, "add", Add);

  //target->Set(Nan::New("Vector").ToLocalChecked(), ctor->GetFunction());
  /* -- original code */

  Nan::Set(target, Nan::New("Vector").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(Vector::New) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  /* original code */
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("Vector::New - called without new keyword").ToLocalChecked());
  }

  // expect exactly 3 arguments
  if(info.Length() != 3) {
    return Nan::ThrowError(Nan::New("Vector::New - expected arguments x, y, z").ToLocalChecked());
  }

  // expect arguments to be numbers
  if(!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    return Nan::ThrowError(Nan::New("Vector::New - expected arguments to be numbers").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  Vector* vec = new Vector();
  vec->Wrap(info.Holder());

  // initialize it's values
  // vec->x = info[0]->NumberValue();
  // vec->y = info[1]->NumberValue();
  // vec->z = info[2]->NumberValue();
  /* -- original code */

  vec->x = info[0]->NumberValue(context).FromMaybe(0);
  vec->y = info[1]->NumberValue(context).FromMaybe(0);
  vec->z = info[2]->NumberValue(context).FromMaybe(0);

  /* original code */
  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
  /* -- original code */
}

NAN_GETTER(Vector::HandleGetters) {
  Vector* self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "x") {
    info.GetReturnValue().Set(self->x);
  } else if (propertyName == "y") {
    info.GetReturnValue().Set(self->y);
  } else if (propertyName == "z") {
    info.GetReturnValue().Set(self->z);
  } else {
    info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_SETTER(Vector::HandleSetters) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  /* original code */
  Vector* self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

  if(!value->IsNumber()) {
    return Nan::ThrowError(Nan::New("expected value to be a number").ToLocalChecked());
  }

  std::string propertyName = std::string(*Nan::Utf8String(property));
  
  // if (propertyName == "x") {
  //   self->x = value->NumberValue();
  // } else if (propertyName == "y") {
  //   self->y = value->NumberValue();
  // } else if (propertyName == "z") {
  //   self->z = value->NumberValue();
  // }
  /* -- original code */

  if (propertyName == "x") {
    self->x = value->NumberValue(context).FromMaybe(0);
  } else if (propertyName == "y") {
    self->y = value->NumberValue(context).FromMaybe(0);
  } else if (propertyName == "z") {
    self->z = value->NumberValue(context).FromMaybe(0);
  }
}

NAN_METHOD(Vector::Add) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  
  // unwrap this Vector
  Vector * self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

  if (!Nan::New(Vector::constructor)->HasInstance(info[0])) {
    return Nan::ThrowError(Nan::New("Vector::Add - expected argument to be instance of Vector").ToLocalChecked());
  }
  // unwrap the Vector passed as argument
  /* original code
  Vector * otherVec = Nan::ObjectWrap::Unwrap<Vector>(info[0]->ToObject());
  */
  Vector * otherVec = Nan::ObjectWrap::Unwrap<Vector>(info[0]->ToObject(context).ToLocalChecked());

  // specify argument counts and constructor arguments
  const int argc = 3;
  v8::Local<v8::Value> argv[argc] = {
    Nan::New(self->x + otherVec->x),
    Nan::New(self->y + otherVec->y),
    Nan::New(self->z + otherVec->z)
  };

  // get a local handle to our constructor function
  /* original code
  v8::Local<v8::Function> constructorFunc = Nan::New(Vector::constructor)->GetFunction();
  */
  v8::Local<v8::Function> constructorFunc = Nan::New(Vector::constructor)->GetFunction(context).ToLocalChecked();
  // create a new JS instance from arguments
  v8::Local<v8::Object> jsSumVec = Nan::NewInstance(constructorFunc, argc, argv).ToLocalChecked();

  info.GetReturnValue().Set(jsSumVec);
}