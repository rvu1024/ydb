# GRANT

Команда `GRANT` позволяет установить права доступа к объектам схемы для пользователя или группы пользователей.

Синтаксис:

```yql
GRANT {{permission_name} [, ...] | ALL [PRIVILEGES]} ON {path_to_scheme_object [, ...]} TO {role_name [, ...]} [WITH GRANT OPTION]
```

* `permission_name` - имя права доступа к объектам схемы, которое нужно назначить.
* `path_to_scheme_object` - путь до объекта схемы, на который выдаются права.
* `role_name` - имя пользователя или группы, для которого выдаются права на объект схемы.

`WITH GRANT OPTION` - использование этой конструкции наделяет пользователя или группу пользователей правом управлять правами доступа - назначать или отзывать определенные права. Конструкция имееет функцианальность аналогичную выдаче права `"ydb.access.grant"` или `GRANT`.
Субъект, обладающий правом `ydb.access.grant`, не может выдавать права шире, чем обладает сам.

## Права доступа {#permissions-list}

В качестве имен прав доступа можно использовать специфичные для {{ ydb-short-name }} права или соответствующие им ключевые слова. В таблице ниже перечислены возможные имена прав и соответствующие им ключевые слова.
Нужно заметить, что специфичные для {{ ydb-short-name }} права задаются как строки и должны заключаться в одинарные или двойные кавычки.

{{ ydb-short-name }} право | Ключевое слово
---|---
`"ydb.database.connect"` | `CONNECT`
`"ydb.tables.modify"` | `MODIFY TABLES`
`"ydb.tables.read"` | `SELECT TABLES`
`"ydb.generic.list"` | `LIST`
`"ydb.generic.read"` | `SELECT`
`"ydb.generic.write"` | `INSERT`
`"ydb.access.grant"` | `GRANT`
`"ydb.generic.use"` | `USE`
`"ydb.generic.use_legacy"` | `USE LEGACY`
`"ydb.database.create"` | `CREATE`
`"ydb.database.drop"` | `DROP`
`"ydb.generic.manage"` | `MANAGE`
`"ydb.generic.full"` | `FULL`
`"ydb.generic.full_legacy"` | `FULL LEGACY`
`"ydb.granular.select_row"` | `SELECT ROW`
`"ydb.granular.update_row"` | `UPDATE ROW`
`"ydb.granular.erase_row"` | `ERASE ROW`
`"ydb.granular.read_attributes"` | `SELECT ATTRIBUTES`
`"ydb.granular.write_attributes"` | `MODIFY ATTRIBUTES`
`"ydb.granular.create_directory"` | `CREATE DIRECTORY`
`"ydb.granular.create_table"` | `CREATE TABLE`
`"ydb.granular.create_queue"` | `CREATE QUEUE`
`"ydb.granular.remove_schema"` | `REMOVE SCHEMA`
`"ydb.granular.describe_schema"` | `DESCRIBE SCHEMA`
`"ydb.granular.alter_schema"` | `ALTER SCHEMA`

* `ALL [PRIVILEGES]` - используется для указания всех возможных прав на объекты схемы для пользователей или групп. `PRIVILEGES` является необязательным ключевым словом, необходимым для совместимости с SQL стандартом.


## Примеры

* Назначить право `ydb.generic.read` на таблицу `/shop_db/orders` для пользователя `user1`:

  ```yql
  GRANT 'ydb.generic.read' ON `/shop_db/orders` TO user1;
  ```

  Та же команда, с использованием ключевого слова

  ```yql
  GRANT SELECT ON `/shop_db/orders` TO user1;
  ```

* Назначить права `ydb.database.connect`, `ydb.generic.list` на корень базы `/shop_db` для пользователя `user2` и группы `group1`:

  ```yql
  GRANT LIST, CONNECT ON `/shop_db` TO user2, group1;
  ```

* Назначить право `ydb.generic.use` на таблицы `/shop_db/orders` и `/shop_db/sellers` для пользователей `user1@domain`, `user2@domain`:

  ```yql
  GRANT 'ydb.generic.use' ON `/shop_db/orders`, `/shop_db/sellers` TO `user1@domain`, `user2@domain`;
  ```

* Назначить все права на таблицу `/shop_db/sellers` для пользователя `admin_user`:

  ```yql
  GRANT ALL ON `/shop_db/sellers` TO admin_user;
  ```
