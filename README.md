# Finanças Pessoais

## Dependências 
Esse projeto usa a biblioteca `ncurses-6.2` ou superior para desenvolvimento.

No seu terminal você pode rodar as seguintes operações para instalar.

#### Ubundo/Debian
```
sudo apt install libncurses5-dev
```

#### Red Hat/CentOS/Fedora
```
sudo dnf ncurses-devel
```

#### Arch/Manjaro
```
sudo pacman -S ncurses
```

Caso nenhuma desses operações seja possivel, você pode baixar diretamente o [código fonte](http://gnu.c3sl.ufpr.br/ftp/ncurses/) da biblioteca e compilar localmente.

Leia os arquivos `README` e `INSTALL` para obter detalhes sobre como instalá-lo. Geralmente envolve as seguintes operações.

```
tar zxvf ncurses<version>.tar.gz
```

```
cd ncurses<version>
```

```
./configure
```

```
make
```

```
su root
```

```
make install
```
