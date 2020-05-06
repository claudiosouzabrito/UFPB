more off
clear
close all

mu=0.1;
rho=1.0;
[u,v,p,x,y]=cavidade(mu,rho);

u=u';
v=v';
p=p';
figure
contour(x,y,p,'ShowText','on')
hold
figure
quiver(x,y,u,v,'color',[1 0 0])
hold off
xlabel('x');
ylabel('y');
axis equal

