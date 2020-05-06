function [u,v,p,x,y]=canal(mu,rho)
% fluido no canal
% entrada:
%   mu=viscosidade
%   rho=densidade
% saida:
%   u(i,j)=velocidade horizontal no ponto (x(i,j),y(i,j))
%   v(i,j)=velocidade vertical no ponto (x(i,j),y(i,j))
%   p(i,j)=pressao no ponto (x(i,j),y(i,j))
%   x(i,j)=coordenada x do ponto (i,j)
%   y(i,j)=coordenada y do ponto (i,j)

F=1;

nu=mu/rho;
% Definicao de numero de pontos na direcao espacial $x_1$: $nx$, $nx>1$, numero inteiro positivo.
nx=11;
%Definicao de numero de pontos na direcao espacial $x_2$: $ny$, $ny>1$, numero inteiro positivo.
ny=nx;
%Definicao de numero de pontos na direcao temporal   $t$: $nt$, $nt>1$, numero inteiro positivo.
nt=101;
%Definicao do domi­nio espacial   $\Omega=[ax,bx]x[ay,by]$: $ax$, $bx$, $ay$, $by$ numeros reais, $0<=ax<bx$, $0<=ay<by$.
ax=0;
ay=0;
bx=1;
by=1;
%Definicao do domi­nio temporal $\Omega_t=[0,t_{max}]$: $t_{max}$ numero real, $0<t_{max}$.
tmax=1;
%Calculo no espaçamento na direcao espacial $x_1$: $\delta_1=\frac{bx-ax}{nx-1}$.
dx=(bx-ax)/(nx-1);
%Calculo no espaçamento na direcao espacial $x_2$: $\delta_2=\frac{by-ay}{ny-1}$.
dy=(by-ay)/(ny-1);
%Calculo no espaçamento na direcao temporal   $t$: $\delta_3=\frac{t_{max}}{nt-1}$.
dt=tmax/(nt-1);


x=ax:dx:bx;
y=ay:dy:by;
[x,y]=meshgrid(x,y);

% Condicoes Iniciais e na fronteira
u=zeros(nx,ny);
v=zeros(nx,ny);
p=zeros(nx,ny);

rhs=zeros(nx,ny);		% lado direito da equacao de Poisson

% condição de fronteira
% u(:,ny)=1;

for it=1:nt-1

	% calcula (nos pontos do interior) o lado direito da equacao de Poisson
	for i=2:nx-1
		for j=2:ny-1
			dudx=(u(i+1,j)-u(i-1,j))/(2*dx);
			dudy=(u(i,j+1)-u(i,j-1))/(2*dy);
			dvdy=(v(i,j+1)-v(i,j-1))/(2*dy);
			dvdx=(v(i+1,j)-v(i-1,j))/(2*dx);
			rhs(i,j)=rho*( (1/dt)*(dudx+dvdy) -dudx^2 -dvdy^2 -2*dudy*dvdx );
		endfor
	endfor
	% condição de fronteira em \Gamma_1 (trocar i-1 por nx)
	i=1;
	for j=2:ny-1
		dudx=(u(i+1,j)-u(nx,j))/(2*dx);
		dudy=(u(i,j+1)-u(i,j-1))/(2*dy);
		dvdy=(v(i,j+1)-v(i,j-1))/(2*dy);
		dvdx=(v(i+1,j)-v(nx,j))/(2*dx);
		rhs(i,j)=rho*( (1/dt)*(dudx+dvdy) -dudx^2 -dvdy^2 -2*dudy*dvdx );
	endfor
	% condição de fronteira em \Gamma_2 (trocar i+1 por 1)
	i=nx;
	for j=2:ny-1
		dudx=(u(1,j)-u(i-1,j))/(2*dx);
		dudy=(u(i,j+1)-u(i,j-1))/(2*dy);
		dvdy=(v(i,j+1)-v(i,j-1))/(2*dy);
		dvdx=(v(1,j)-v(i-1,j))/(2*dx);
		rhs(i,j)=rho*( (1/dt)*(dudx+dvdy) -dudx^2 -dvdy^2 -2*dudy*dvdx );
	endfor

	% calcula a pressao p usando a equacao de Poisson
	% https://nbviewer.jupyter.org/github/barbagroup/CFDPython/blob/master/lessons/14_Step_11.ipynb
	nit=50;
	for iit=1:nit
	%while 1
		pn=p;
		% calcula nos pontos interiores
		for i=2:nx-1
			for j=2:ny-1
				p(i,j)=(1/(2*(dx^2+dy^2))) * (  (pn(i+1,j)+pn(i-1,j))*dy^2+(pn(i,j+1)+pn(i,j-1))*dx^2 -(rho*dx^2*dy^2)*rhs(i,j)  );
			endfor
		endfor

		% condição de fronteira em \Gamma_1 (trocar i-1 por nx)
		i=1;
		for j=2:ny-1
			p(i,j)=(1/(2*(dx^2+dy^2))) * (  (pn(i+1,j)+pn(nx,j))*dy^2+(pn(i,j+1)+pn(i,j-1))*dx^2 -(rho*dx^2*dy^2)*rhs(i,j)  );
		endfor

		% condição de fronteira em \Gamma_2 (trocar i+1 por 1)
		i=nx;
		for j=2:ny-1
			p(i,j)=(1/(2*(dx^2+dy^2))) * (  (pn(1,j)+pn(i-1,j))*dy^2+(pn(i,j+1)+pn(i,j-1))*dx^2 -(rho*dx^2*dy^2)*rhs(i,j)  );
		endfor

		% condicao de fronteira nas paredes
		p(:,1)=p(:,2);
		p(:,ny)=p(:,ny-1);
	endfor
	%endwhile
	fprintf('it=%i, norm(p-pn)=%f\n',it,norm(p-pn))
	if norm(p-pn)>1e10
		break
	endif
	
	un=u;
	vn=v;
	for i=2:nx-1
		for j=2:ny-1
			u(i,j)=un(i,j) -un(i,j)*dt/dx*(un(i,j)-un(i-1,j)) -vn(i,j)*dt/dy*(un(i,j)-un(i,j-1)) -(dt/(2*rho*dx))*(p(i+1,j)-p(i-1,j)) + nu*(dt/dx^2*(u(i+1,j)-2*u(i,j)+u(i-1,j))+dt/dy^2*(u(i,j+1)-2*u(i,j)+u(i,j-1))) + F*dt;
			v(i,j)=vn(i,j) -un(i,j)*dt/dx*(vn(i,j)-vn(i-1,j)) -vn(i,j)*dt/dy*(vn(i,j)-vn(i,j-1)) -(dt/(2*rho*dy))*(p(i,j+1)-p(i,j-1)) + nu*(dt/dx^2*(v(i+1,j)-2*v(i,j)+v(i-1,j))+dt/dy^2*(v(i,j+1)-2*v(i,j)+v(i,j-1)));
		endfor
	endfor

	% condição de fronteira em \Gamma_1 (trocar i-1 por nx)
	i=1;
	for j=2:ny-1
		u(i,j)=un(i,j) -un(i,j)*dt/dx*(un(i,j)-un(nx,j)) -vn(i,j)*dt/dy*(un(i,j)-un(i,j-1)) -(dt/(2*rho*dx))*(p(i+1,j)-p(nx,j)) + nu*(dt/dx^2*(u(i+1,j)-2*u(i,j)+u(nx,j))+dt/dy^2*(u(i,j+1)-2*u(i,j)+u(i,j-1))) + F*dt;
		v(i,j)=vn(i,j) -un(i,j)*dt/dx*(vn(i,j)-vn(nx,j)) -vn(i,j)*dt/dy*(vn(i,j)-vn(i,j-1)) -(dt/(2*rho*dy))*(p(i,j+1)-p(i,j-1)) + nu*(dt/dx^2*(v(i+1,j)-2*v(i,j)+v(nx,j))+dt/dy^2*(v(i,j+1)-2*v(i,j)+v(i,j-1)));
	endfor
	% condição de fronteira em \Gamma_2 (trocar i+1 por 1)
	i=nx;
	for j=2:ny-1
		u(i,j)=un(i,j) -un(i,j)*dt/dx*(un(i,j)-un(i-1,j)) -vn(i,j)*dt/dy*(un(i,j)-un(i,j-1)) -(dt/(2*rho*dx))*(p(1,j)-p(i-1,j)) + nu*(dt/dx^2*(u(1,j)-2*u(i,j)+u(i-1,j))+dt/dy^2*(u(i,j+1)-2*u(i,j)+u(i,j-1))) + F*dt;
		v(i,j)=vn(i,j) -un(i,j)*dt/dx*(vn(i,j)-vn(i-1,j)) -vn(i,j)*dt/dy*(vn(i,j)-vn(i,j-1)) -(dt/(2*rho*dy))*(p(i,j+1)-p(i,j-1)) + nu*(dt/dx^2*(v(1,j)-2*v(i,j)+v(i-1,j))+dt/dy^2*(v(i,j+1)-2*v(i,j)+v(i,j-1)));
	endfor


endfor
