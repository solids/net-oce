#include "handler.h"

#include <BRepBuilderAPI_Copy.hxx>

HANDLER(op_copy, "handle") {

  if (req->argument_size() != 1) {
    HANDLER_ERROR("1 argument required: handle")
    return true;
  }

  shape_id_t handle = req->argument(0).uint32_value();

  TopoDS_Shape shape = editor->getShape(handle);
  if (shape.IsNull()) {
    HANDLER_ERROR("specified object does not exist")
    return true;
  }

  BRepBuilderAPI_Copy builder;
  builder.Perform(shape);
  shape_id_t shape_id = editor->addShape(req, builder.Shape());

  NetOCE_Value *val = res->add_value();
  val->set_type(NetOCE_Value::SHAPE_HANDLE);
  val->set_uint32_value(shape_id);
  return true;
}
