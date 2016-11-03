#-------------------------------------------------
#
# Project created by QtCreator 2016-10-26T03:35:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nex
TEMPLATE = app


SOURCES += main.cpp \
    ../../module/nxs/src/ndb/engine/sql/expression.cpp \
    ../../module/nxs/src/ndb/engine/sql/model.cpp \
    ../../module/nxs/src/ndb/engine/sql/sql.cpp \
    ../../module/nxs/src/ndb/engine/sql/type.cpp \
    ../../module/nxs/src/ndb/user_model.cpp \
    ../../module/nxs/src/nds/data.cpp \
    ../../module/nxs/src/nds/nds.cpp \
    ../../module/nxs/src/nxs/command/file.cpp \
    ../../module/nxs/src/nxs/command/nxs.cpp \
    ../../module/nxs/src/nxs/command/resource.cpp \
    ../../module/nxs/src/nxs/command/user.cpp \
    ../../module/nxs/src/nxs/network/connexion/input.cpp \
    ../../module/nxs/src/nxs/network/connexion/output.cpp \
    ../../module/nxs/src/nxs/network/protocol/http.cpp \
    ../../module/nxs/src/nxs/network/protocol/nex.cpp \
    ../../module/nxs/src/nxs/network/connexion.cpp \
    ../../module/nxs/src/nxs/network/data.cpp \
    ../../module/nxs/src/nxs/network/header.cpp \
    ../../module/nxs/src/nxs/network/param.cpp \
    ../../module/nxs/src/nxs/network/protocol.cpp \
    ../../module/nxs/src/nxs/network/request.cpp \
    ../../module/nxs/src/nxs/network/request_base.cpp \
    ../../module/nxs/src/nxs/network/request_decoder.cpp \
    ../../module/nxs/src/nxs/network/request_encoder.cpp \
    ../../module/nxs/src/nxs/network/server.cpp \
    ../../module/nxs/src/nxs/resource/type.cpp \
    ../../module/nxs/src/nxs/utility/file.cpp \
    ../../module/nxs/src/nxs/command.cpp \
    ../../module/nxs/src/nxs/config.cpp \
    ../../module/nxs/src/nxs/core.cpp \
    ../../module/nxs/src/nxs/database.cpp \
    ../../module/nxs/src/nxs/error.cpp \
    ../../module/nxs/src/nxs/error_message.cpp \
    ../../module/nxs/src/nxs/log.cpp \
    ../../module/nxs/src/nxs/resource.cpp \
    ../../module/nxs/src/nxs/user.cpp \
    ../../module/nxs/src/ndb/engine/sql/sqlite3.c

HEADERS  += \
    ../../module/nxs/src/ndb/engine/sql/expression.hpp \
    ../../module/nxs/src/ndb/engine/sql/sql.hpp \
    ../../module/nxs/src/ndb/engine/sql/sqlite3.h \
    ../../module/nxs/src/ndb/engine/sql/type.hpp \
    ../../module/nxs/src/ndb/engine/sql/value.hpp \
    ../../module/nxs/src/ndb/engine/engine.hpp \
    ../../module/nxs/src/ndb/engine/include.hpp \
    ../../module/nxs/src/ndb/engine/setup.hpp \
    ../../module/nxs/src/ndb/engine/type.hpp \
    ../../module/nxs/src/ndb/utility/benchmark.hpp \
    ../../module/nxs/src/ndb/utility/trait.hpp \
    ../../module/nxs/src/ndb/engine.hpp \
    ../../module/nxs/src/ndb/entity.hpp \
    ../../module/nxs/src/ndb/error.hpp \
    ../../module/nxs/src/ndb/expression.hpp \
    ../../module/nxs/src/ndb/field.hpp \
    ../../module/nxs/src/ndb/field_base.hpp \
    ../../module/nxs/src/ndb/field_option.hpp \
    ../../module/nxs/src/ndb/line.hpp \
    ../../module/nxs/src/ndb/model.hpp \
    ../../module/nxs/src/ndb/query.hpp \
    ../../module/nxs/src/ndb/result.hpp \
    ../../module/nxs/src/ndb/setup.hpp \
    ../../module/nxs/src/ndb/table.hpp \
    ../../module/nxs/src/ndb/table_join.hpp \
    ../../module/nxs/src/ndb/table_option.hpp \
    ../../module/nxs/src/ndb/type.hpp \
    ../../module/nxs/src/ndb/user_model.hpp \
    ../../module/nxs/src/ndb/version.hpp \
    ../../module/nxs/src/nds/data.hpp \
    ../../module/nxs/src/nds/encoder.hpp \
    ../../module/nxs/src/nds/json.hpp \
    ../../module/nxs/src/nds/nds.hpp \
    ../../module/nxs/src/nxs/module/module.hpp \
    ../../module/nxs/src/nxs/network/connexion/input.hpp \
    ../../module/nxs/src/nxs/network/connexion/output.hpp \
    ../../module/nxs/src/nxs/network/protocol/http.hpp \
    ../../module/nxs/src/nxs/network/protocol/nex.hpp \
    ../../module/nxs/src/nxs/network/buffer.hpp \
    ../../module/nxs/src/nxs/network/connexion.hpp \
    ../../module/nxs/src/nxs/network/data.hpp \
    ../../module/nxs/src/nxs/network/header.hpp \
    ../../module/nxs/src/nxs/network/param.hpp \
    ../../module/nxs/src/nxs/network/protocol.hpp \
    ../../module/nxs/src/nxs/network/request.hpp \
    ../../module/nxs/src/nxs/network/request_base.hpp \
    ../../module/nxs/src/nxs/network/server.hpp \
    ../../module/nxs/src/nxs/network/socket.hpp \
    ../../module/nxs/src/nxs/os/share.hpp \
    ../../module/nxs/src/nxs/resource/type.hpp \
    ../../module/nxs/src/nxs/setup/connexion.hpp \
    ../../module/nxs/src/nxs/setup/request.hpp \
    ../../module/nxs/src/nxs/utility/benchmark.hpp \
    ../../module/nxs/src/nxs/utility/file.hpp \
    ../../module/nxs/src/nxs/utility/reflector.hpp \
    ../../module/nxs/src/nxs/utility/trait.hpp \
    ../../module/nxs/src/nxs/command.hpp \
    ../../module/nxs/src/nxs/config.hpp \
    ../../module/nxs/src/nxs/constant.hpp \
    ../../module/nxs/src/nxs/core.hpp \
    ../../module/nxs/src/nxs/database.hpp \
    ../../module/nxs/src/nxs/error.hpp \
    ../../module/nxs/src/nxs/log.hpp \
    ../../module/nxs/src/nxs/resource.hpp \
    ../../module/nxs/src/nxs/setup.hpp \
    ../../module/nxs/src/nxs/user.hpp \
    ../../module/nxs/src/nxs/version.hpp

CONFIG += mobility
MOBILITY = 

