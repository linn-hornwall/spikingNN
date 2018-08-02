file1=fopen('../build/sum_spikes.txt','r');
formatSpec='%u %u';
sizeA=[20000 Inf];
A=fscanf(file1,formatSpec,sizeA);
fclose(file1);
A=A';
file2=fopen('../build/spikes.txt','r');
formatSpec='%u %u';
sizeB=[50 Inf];
B= fscanf(file2,formatSpec,sizeB);
fclose(file2);


subplot(2,1,2),stem(A,'k', 'Marker', 'none');
title('Sum of spikes at each time step')
xlabel('Timestep (ms)')
ylabel('Sum of spikes')
axis([10000 12000.8 0 200])
set(gca,'xTick',10000:500:12000.8)
set(gca,'yTick',0:50:200)
set(gca,'xTick',10000:500:12000.8)
set(gca,'xTickLabel',{'1000','1050','1100','1150','1200'})


subplot(2,1,1);
size=5;
spy(B,'k',size);
pbaspect([5 1 1])
axis([10000 12000.8 0 50.8])
title('Number of neuron spiking at each time step')
set(gca,'Ydir','Normal')
set(gca,'yTick',0:10:50.8)
set(gca,'yTickLabel',{'0','10','20','30','40','50'})
set(gca,'xTick',10000:500:12000.8)
set(gca,'xTickLabel',{'1000','1050','1100','1150','1200'})
xlabel('Timestep (ms)')
ylabel('Neurons that spike')
