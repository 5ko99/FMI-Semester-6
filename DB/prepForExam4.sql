set schema DB2MOVIE;
select title, year, length
from movie
where length > 120 and year < 1990
   or length is NULL;

--2
SELECT NAME
FROM MOVIESTAR
WHERE GENDER = 'M'
  AND BIRTHDATE IN
      (
          SELECT MAX(BIRTHDATE)
          FROM MOVIESTAR
          WHERE GENDER = 'M'
      );

-- SECOND WAY
SELECT NAME
FROM MOVIESTAR
WHERE GENDER = 'M'
  AND BIRTHDATE >= ALL (SELECT BIRTHDATE
                        FROM MOVIESTAR
                        WHERE GENDER = 'M');

--3
SET SCHEMA DB2SHIPS;
select c.country, count(o.result) as Sunk
from classes c
         left join ships s on c.class = s.class
         left join outcomes o on s.name = o.ship
where result = 'sunk'
   or result is NULL
group by c.country;

-- 4
set schema DB2PC;

select distinct pc.model
from pc
         join product p on pc.model = p.model
where price < (select min(price)
               from laptop
                        join product t
                             on laptop.model = t.model
               where t.maker = p.maker);

--variant 2
set schema DB2MOVIE;
--1
select NAME, GENDER
from MOVIESTAR
where name like 'J%'
  and year(BIRTHDATE) > 1948
order by NAME DESC;

--2
set schema DB2SHIPS;
select NAME, COUNTRY
from SHIPS
         left join OUTCOMES O on SHIPS.NAME = O.SHIP
         right join CLASSES C2 on SHIPS.CLASS = C2.CLASS
where RESULT = 'sunk'
   or BATTLE is NULL;

--3
set schema DB2PC;
select MODEL
from LAPTOP
where SCREEN = 11 or SCREEN = 15;

--4
set schema DB2PC;
select MODEL
from PC
group by MODEL
having avg(PRICE)<(select min(PRICE) from LAPTOP);

-- variant 3
--1
set schema DB2SHIPS;
select distinct SHIP
from OUTCOMES
where SHIP like 'C%' or ship like 'K&';

--3
set schema DB2MOVIE;
select movietitle, movieyear
from STARSIN
group by movietitle, movieyear
having count(*) > 2;

--2
set schema DB2PC;
select p1.code, maker,  count(p2.code)
from pc p1, pc p2, product
where p1.price <= p2.price and p1.model=product.model and p2.model=product.model
group by p1.code, maker;

-- 4
select pc.model, sum(price) from pc
join product p on pc.model=p.model
group by pc.model
having sum(price) < (select sum(price) from laptop
	join product t
	on laptop.model=t.model);

