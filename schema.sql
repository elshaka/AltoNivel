--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: alto_nivel; Type: DATABASE; Schema: -; Owner: postgres
--

DROP DATABASE IF EXISTS alto_nivel;

CREATE DATABASE alto_nivel WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'es_VE.UTF-8' LC_CTYPE = 'es_VE.UTF-8';


ALTER DATABASE alto_nivel OWNER TO postgres;

\connect alto_nivel

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: clientes; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE clientes (
    id integer NOT NULL,
    nombre character varying(50) NOT NULL,
    apellido character varying(50) NOT NULL,
    cedula character varying(50) NOT NULL,
    direccion character varying(200) NOT NULL,
    telefono character varying(20) NOT NULL
);


ALTER TABLE public.clientes OWNER TO postgres;

--
-- Name: clientes_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE clientes_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.clientes_id_seq OWNER TO postgres;

--
-- Name: clientes_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE clientes_id_seq OWNED BY clientes.id;


--
-- Name: facturas; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE facturas (
    id integer NOT NULL,
    cliente_id integer NOT NULL,
    tipo character varying(10),
    numero integer NOT NULL,
    fecha_emision timestamp without time zone NOT NULL,
    fecha_vencimiento timestamp without time zone,
    monto real NOT NULL,
    saldo_pendiente real,
    estado character varying(20) NOT NULL
);


ALTER TABLE public.facturas OWNER TO postgres;

--
-- Name: facturas_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE facturas_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.facturas_id_seq OWNER TO postgres;

--
-- Name: facturas_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE facturas_id_seq OWNED BY facturas.id;


--
-- Name: facturas_numero_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE facturas_numero_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.facturas_numero_seq OWNER TO postgres;

--
-- Name: facturas_numero_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE facturas_numero_seq OWNED BY facturas.numero;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY clientes ALTER COLUMN id SET DEFAULT nextval('clientes_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY facturas ALTER COLUMN id SET DEFAULT nextval('facturas_id_seq'::regclass);


--
-- Name: numero; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY facturas ALTER COLUMN numero SET DEFAULT nextval('facturas_numero_seq'::regclass);


--
-- Name: pk_clientes; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY clientes
    ADD CONSTRAINT pk_clientes PRIMARY KEY (id);


--
-- Name: pk_facturas; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY facturas
    ADD CONSTRAINT pk_facturas PRIMARY KEY (id);


--
-- Name: fk_clientes; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY facturas
    ADD CONSTRAINT fk_clientes FOREIGN KEY (cliente_id) REFERENCES clientes(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

