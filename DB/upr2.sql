set schema DB2MOVIE;

select MOVIESTAR.BIRTHDATE as birhadate
from MOVIESTAR
where NAME='Sandra Bullock';

select NAME as oldName
from MOVIESTAR
where BIRTHDATE = '1948-12-05';

select name as name1
from MOVIESTAR
where year(BIRTHDATE) between 1948 and 1950;

set schema DB2PC;

select MODEL, SPEED as  MHZ, HD as GB
from PC
where price < 1200;

select distinct MAKER
from PRODUCT
where type = 'Printer';

select MODEL, SPEED, HD
from PC
where (cd='12x' or cd='16x') and price<2000;

select DISTINCT MODEL
from PC;

set schema DB2SHIPS;

select NAME
from SHIPS
where name like '% %' and name not like '% % %';