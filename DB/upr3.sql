SET SCHEMA MOVIES;

-- I
select starname
from starsin, moviestar
where movietitle='Terms of Endearment' and starname=name and gender='M';

-- II

select starname
from starsin
where movietitle='Terms of Endearment'

intersect

select name
from moviestar
where gender='M';


select starname
from starsin, movie
where studioname='MGM' and year=1995 and movietitle=title and year=movieyear;


select distinct name
from movie, movieexec
where producerc#=cert# and studioname='MGM';


select *
from movie m1, movie m2
where m2.title='Gone With the Wind' and m1.year<>m2.year and m1.title<>m2.title and m1.length > m2.length;


select *
from movieexec me1, movieexec me2
where me1.networth>me2.networth and me1.cert#<>me2.cert# and me2.name='Merv Griffin';


SET SCHEMA PC;


select maker, speed
from product,laptop
where product.model = laptop.model and hd > 9;


select distinct p.model, l.price as Price, p.type
from product p, laptop l
where maker='B' and p.model=l.model

union

select distinct p.model, pc.price as Price, p.type
from product p, pc
where maker='B' and p.model=pc.model

union

select p.model, pr.price as Price, p.type
from product p, printer pr
where maker='B' and p.model=pr.model;


select distinct pc1.hd
from pc as pc1, pc as pc2
where pc1.model<>pc2.model and pc1.hd=pc2.hd
order by pc1.hd;



select distinct pc1.hd
from pc as pc1, pc as pc2, pc as pc3
where pc1.model<>pc2.model and pc1.model<>pc3.model and pc2.model<>pc3.model
and pc1.hd=pc2.hd and pc2.hd=pc3.hd
order by pc1.hd;



select m1.model, m2.model
from pc m1, pc m2
where m1.speed=m2.speed  and m1.ram=m2.ram and m1.model<m2.model;


select distinct p1.maker, p1.model
from product p1, product p2, pc as pc1, pc as pc2
where p1.maker=p2.maker and p1.model<>p2.model and pc1.speed>400 and pc1.model=p1.model and
pc2.speed>400 and pc2.model=p2.model;


SET SCHEMA SHIPS;


select s.name
from ships s, classes c
where s.class=c.class and c.displacement>35000;


select s.name, c.displacement, c.numguns
from ships s, classes c, outcomes o
where o.battle='Guadalcanal' and o.ship=s.name and c.class=s.class;


-- I

select c1.country, c1.type, c2.type
from classes c1, classes c2
where c1.country=c2.country and c1.type='bb' and c2.type='bc';

-- II

(select country
from classes
where type='bb')

intersect

(select country
from classes
where type='bc');

select distinct o1.battle
from classes c1, ships s1, outcomes o1,
     classes c2, ships s2, outcomes o2,
     classes c3, ships s3, outcomes o3
where c1.class=s1.class and s1.name=o1.ship
 and c2.class=s2.class and s2.name=o2.ship
 and c3.class=s3.class and s3.name=o3.ship
 and c1.country=c2.country and c1.country=c3.country
 and o1.battle=o2.battle and o1.battle=o3.battle
 and s1.name<>s2.name and s1.name<>s3.name and s2.name<>s3.name;


select o1.ship
from outcomes o1, battles b1, outcomes o2, battles b2
where o1.battle=b1.name
 and o2.battle=b2.name
 and o1.ship=o2.ship
 and b1.date<b2.date
and o1.result='damaged';

