package prod_cons;

public class Producer extends Thread{
	
	private Production temp;
	
	public Producer(Production product){
		temp = product;
	}
	
	public void run(){
		
		for(int i = 0; i < 10; i++)
			temp.prod();
		
	}


}
