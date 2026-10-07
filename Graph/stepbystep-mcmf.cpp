
const ll INF = 1e18 ;

struct Edge 
{
    int to ;
    int rev ;
    ll cap ;
    ll flow ;
    ll cost ;
};

class MCMF 
{
private:
    int n ;
    vector < vector < Edge > > adj ;
    vector < ll > dist ;
    vector < ll > potential ;
    vector < int > parent_node ;
    vector < int > parent_edge ;

    // Dijkstra باستخدام Potentials لضمان عدم وجود أضلع سالبة أثناء البحث
    bool dijkstra(int s , int t) 
    {
        fill(dist.begin() , dist.end() , INF) ;
        priority_queue < pair < ll , int > , vector < pair < ll , int > > , greater < pair < ll , int > > > pq ;

        dist[s] = 0 ;
        pq.push({0 , s}) ;

        while (!pq.empty()) {
            auto [d , u] = pq.top() ;
            pq.pop() ;

            if (d  > dist[u]) continue ;

            for (int i = 0 ; i < (int)adj[u].size() ; i ++ ) 
            {
                const Edge &e = adj[u][i] ;
                if (e.cap - e.flow > 0) 
                {
                    ll reduced_cost = e.cost + potential[u] - potential[e.to] ;
                    if (dist[e.to]  > dist[u] + reduced_cost) 
                    {
                        dist[e.to] = dist[u] + reduced_cost ;
                        parent_node[e.to] = u ;
                        parent_edge[e.to] = i ;
                        pq.push({dist[e.to] , e.to}) ;
                    }
                }
            }
        }

        if (dist[t] == INF) return false ;

        for (int i = 0 ; i < n ; i ++) 
        {
            if (dist[i] != INF) potential[i] += dist[i] ;
        }

        return true ;
    }

    // تهيئة الـ Potentials في البداية فقط بـ SPFA لو الرسم فيه تكاليف سالبة مبدئياً
    void init_potentials(int s) 
    {
        fill(potential.begin() , potential.end() , INF) ;
        vector < bool > in_queue(n , false) ;
        queue < int > q ;

        potential[s] = 0 ;
        q.push(s) ;
        in_queue[s] = true ;

        while (!q.empty()) 
        {
            int u = q.front() ; q.pop() ;
            in_queue[u] = false ;

            for (auto &e : adj[u]) 
            {
                if (e.cap - e.flow  > 0 && potential[e.to]  > potential[u] + e.cost) 
                {
                    potential[e.to] = potential[u] + e.cost ;
                    if (!in_queue[e.to]) {
                        q.push(e.to) ;
                        in_queue[e.to] = true ;
                    }
                }
            }
        }

        for (int i = 0 ; i < n ; i ++ ) if (potential[i] == INF) potential[i] = 0 ;
    }

public:
    MCMF(int n) : n(n) , adj(n) , dist(n) , potential(n , 0) , parent_node(n) , parent_edge(n) {}

    void add_edge(int u , int v , ll cap , ll cost) 
    {
        Edge a = {v , (int)adj[v].size() , cap , 0 , cost} ;
        Edge b = {u , (int)adj[u].size() , 0 , 0 , -cost} ;
        adj[u].push_back(a) ;
        adj[v].push_back(b) ;
    }

    // ضخ وحدة تدفق واحدة فقط (Step-by-Step) وترجع {flow_pushed , cost_of_this_step}
    pair < ll , ll > solve(int s , int t , bool is_first_step = false) 
    {
        if (is_first_step) 
        {
            init_potentials(s) ;
        }

        if (!dijkstra(s , t)) return {0 , 0} ;

        ll push = 1 ; // ضخ unit واحدة لكل خطوة
        int cur = t ;
        while (cur != s) 
        {
            int p = parent_node[cur] ;
            int idx = parent_edge[cur] ;
            push = min(push , adj[p][idx].cap - adj[p][idx].flow) ;
            cur = p ;
        }

        ll step_cost = 0 ;
        cur = t ;
        while (cur != s) 
        {
            int p = parent_node[cur] ;
            int idx = parent_edge[cur] ;
            adj[p][idx].flow += push ;
            int rev_idx = adj[p][idx].rev ;
            adj[cur][rev_idx].flow -= push ;
            step_cost += push * adj[p][idx].cost ;
            cur = p ;
        }

        return {push , step_cost} ;
    }
};