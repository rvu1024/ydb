# REVOKE

Команда `REVOKE` позволяет отозвать права доступа к объектам схемы для пользователей или групп пользователей.

Синтаксис:

```yql
REVOKE [GRANT OPTION FOR] {{permission_name} [, ...] | ALL [PRIVILEGES]} ON {path_to_scheme_object [, ...]} FROM {role_name [, ...]}
```

* `permission_name` - имя права доступа к объектам схемы, которое нужно отозвать.
* `path_to_scheme_object` - путь до объекта схемы, с которого отзываются права.
* `role_name` - имя пользователя или группы, для которого отзываются права на объект схемы.

`GRANT OPTION FOR` - использование этой конструкции отзывает у пользователя или группы право управлять правами доступа. Все ранее выданные этим пользователем права остаются в силе. Конструкция имеет функцианальность аналогичную отзыву права `"ydb.access.grant"` или `GRANT`.

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

* Отозвать право `ydb.generic.read` на таблицу `/shop_db/orders` у пользователя `user1`:

  ```yql
  REVOKE 'ydb.generic.read' ON `/shop_db/orders` FROM user1;
  ```

  Та же команда, с использованием ключевого слова

  ```yql
  REVOKE SELECT ON `/shop_db/orders` FROM user1;
  ```

* Отозвать права `ydb.database.connect`, `ydb.generic.list` на корень базы `/shop_db` у пользователя `user2` и группы `group1`:

  ```yql
  REVOKE LIST, CONNECT ON `/shop_db` FROM user2, group1;
  ```

* Отозвать право `ydb.generic.use` на таблицы `/shop_db/orders` и `/shop_db/sellers` у пользователей `user1@domain`, `user2@domain`:

  ```yql
  REVOKE 'ydb.generic.use' ON `/shop_db/orders`, `/shop_db/sellers` FROM `user1@domain`, `user2@domain`;
  ```

* Отозвать все права на таблицу `/shop_db/sellers` для пользователя `user`:

  ```yql
  REVOKE ALL ON `/shop_db/sellers` FROM user;
  ```
