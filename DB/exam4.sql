set schema DB2MOVIE;
--1zad
select title, year
from movie
where title like '%Star%Trek%'
order by year, title;

--2zad
select STARNAME, STUDIONAME
from  MOVIE
left join STARSIN S on MOVIE.TITLE = S.MOVIETITLE and MOVIE.YEAR = S.MOVIEYEAR
left join STUDIO S2 on S2.NAME = MOVIE.STUDIONAME
where STARNAME = (select min(STARNAME) from STARSIN
    join MOVIE M on M.TITLE = STARSIN.MOVIETITLE and M.YEAR = STARSIN.MOVIEYEAR
    join STUDIO S3 on M.STUDIONAME = S3.NAME where
    S.MOVIETITLE = M.TITLE and M.STUDIONAME = name );

-- 3
select title, year
from MOVIE
         join STARSIN S on MOVIE.TITLE = S.MOVIETITLE and MOVIE.YEAR = S.MOVIEYEAR
         join MOVIESTAR M on S.STARNAME = M.NAME
where (MOD(year(BIRTHDATE), 4) = 0 and MOD(year(BIRTHDATE), 100) = 0
    and MOD(year(BIRTHDATE), 400) = 0)
   or (MOD(year(BIRTHDATE), 4) = 0
    and MOD(year(BIRTHDATE), 100) != 0);


-- 4
select STARNAME
from STARSIN
         join MOVIE M on STARSIN.MOVIETITLE = M.TITLE and STARSIN.MOVIEYEAR = M.YEAR
         join MOVIEEXEC M2 on M.PRODUCERC# = M2.CERT#
where NETWORTH = (select min(NETWORTH) from MOVIEEXEC);

-- 5
select name, title
from STUDIO
join MOVIE M on STUDIO.NAME = M.STUDIONAME
where year = (select min(year) from movie where studioname = name);

--5 without join
select m.STUDIONAME, TITLE
from MOVIE m
where year = (select min(year) from MOVIE where m.STUDIONAME = STUDIONAME);

