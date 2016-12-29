namespace vmc
{
    const char *USERS_TABLE = R"(
CREATE TABLE IF NOT EXISTS `users` (
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `username` VARCHAR(32) NOT NULL,
    `password` VARCHAR(255) NOT NULL,
    `email` VARCHAR(64) NOT NULL,
    `privilege` TINYINT(4) NOT NULL DEFAULT '0',
    `create_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`)
)  ENGINE=INNODB DEFAULT CHARSET=UTF8;
    )";
}
