import React, { useState, useEffect, useRef } from 'react';
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  Filler
} from 'chart.js';
import './App.css';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  Filler
);

function App() {
  // 데이터 포인트 수를 60으로 설정 (3분 * 60초 / 3초 = 60)
  const DATA_POINTS = 60;

  // 각 차트의 데이터 (6개 차트, 각 차트는 statIndex별 데이터 포인트 배열)
  const [data, setData] = useState(Array(6).fill().map(() => ({})));

  // 공통 레이블 (60개 레이블)
  const [labels, setLabels] = useState(Array(DATA_POINTS).fill('00:00:00'));

  // 세션 데이터
  const [sessionData, setSessionData] = useState([]);

  // 표시할 차트 제어 (기본적으로 첫 번째 차트만 표시)
  const [visibleCharts, setVisibleCharts] = useState([true, false, false, false, false, false]);

  // 통계 이름 목록
  const [statNames, setStatNames] = useState([]);

  // 드롭다운 열림 상태를 관리하는 상태 변수 추가 (각 차트마다 독립적으로 관리)
  const [dropdownOpen, setDropdownOpen] = useState(Array(6).fill(false));

  // 체크박스 상태를 관리하는 상태 변수 추가 (각 차트마다 선택된 통계를 관리)
  const [checkedStats, setCheckedStats] = useState(Array(6).fill().map(() => []));

  const intervalRef = useRef(null);

  const parseTimeString = (timeStr) => {
    const year = timeStr.substring(0, 4);
    const month = timeStr.substring(4, 6);
    const day = timeStr.substring(6, 8);
    const hour = timeStr.substring(8, 10);
    const minute = timeStr.substring(10, 12);
    const second = timeStr.substring(12, 14);
    return new Date(`${year}-${month}-${day}T${hour}:${minute}:${second}`);
  };

  // 초기 데이터 큐를 처리하는 함수
  const processQueueData = (queueData) => {
    console.log("Processing queue data:", queueData);
    if (!queueData || queueData.length === 0) return;

    // 각 차트에 대한 새로운 데이터 객체 초기화
    const newData = Array(6).fill().map(() => ({}));

    // 모든 데이터 포인트의 타임스탬프를 저장할 배열
    const allTimestamps = [];

    queueData.forEach((dataItem, idx) => {
      try {
        const parsedData = typeof dataItem === 'string' ? JSON.parse(dataItem) : dataItem;
        console.log(`Parsed data item ${idx}:`, parsedData);

        const sessionArray = parsedData.SESSION.filter(session => session.SQL_ADDRESS.trim() !== "0") || [];
        setSessionData(sessionArray);

        // 선택된 통계에 따라 각 차트에 데이터 추가
        checkedStats.forEach((statSelections, chartIndex) => {
          statSelections.forEach((isSelected, statIdx) => {
            if (isSelected) {
              const value = parsedData.SYSSTAT[statIdx]?.VALUE || 0;
              if (!newData[chartIndex][statIdx]) {
                newData[chartIndex][statIdx] = [];
              }
              newData[chartIndex][statIdx].push(value);
              while (newData[chartIndex][statIdx].length < DATA_POINTS) {
                newData[chartIndex][statIdx].unshift(0);
              }
            }
          });
        });

        // 타임스탬프 파싱 및 저장
        const timestamp = parseTimeString(parsedData.TIME.toString());
        allTimestamps.push(timestamp);
      } catch (error) {
        console.error(`Error parsing queued data item ${idx}:`, error);
      }
    });

    // 기존 데이터에 새 데이터 추가
    setData(prevData => {
      const updatedData = [...prevData];
      for (let chartIndex = 0; chartIndex < 6; chartIndex++) {
        Object.keys(newData[chartIndex]).forEach(statIdx => {
          if (!updatedData[chartIndex][statIdx]) {
            updatedData[chartIndex][statIdx] = [];
          }
          updatedData[chartIndex][statIdx] = [
            ...updatedData[chartIndex][statIdx],
            ...newData[chartIndex][statIdx]
          ];

          if (updatedData[chartIndex][statIdx].length > DATA_POINTS) {
            updatedData[chartIndex][statIdx] = updatedData[chartIndex][statIdx].slice(-DATA_POINTS);
          }
        });
      }
      return updatedData;
    });

    if (allTimestamps.length > 0) {
      const latestTime = allTimestamps[allTimestamps.length - 1];
      console.log("Latest time from queue:", latestTime);
      const newLabels = [];

      for (let i = DATA_POINTS - 1; i >= 0; i--) {
        const timeLabel = new Date(latestTime.getTime() - i * 3000);
        newLabels.push(timeLabel.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: false }));
      }

      setLabels(newLabels);
    }
  };

  // 초기 데이터 큐 가져오기
  useEffect(() => {
    const fetchInitialData = async () => {
      console.log("Fetching initial data queue...");
      try {
        const response = await fetch('/api/dataQueue');
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        const queueData = await response.json();
        console.log("Fetched initial data queue:", queueData);
        processQueueData(queueData);
      } catch (error) {
        console.error('Error fetching initial data queue:', error);
      }
    };

    fetchInitialData();
  }, [checkedStats]);

  // 통계 이름 가져오기
  useEffect(() => {
    const fetchStatNames = async () => {
      console.log("Fetching stat names...");
      try {
        const response = await fetch('/statnames');
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        const data = await response.json();
        console.log("Fetched stat names:", data);
        setStatNames(data);

        setCheckedStats(Array(6).fill().map(() => data.map((_, idx) => idx === 0)));
      } catch (error) {
        console.error('Error fetching stat names:', error);
      }
    };

    fetchStatNames();
  }, []);

  // 3초마다 새로운 데이터 가져오기
  useEffect(() => {
    const fetchData = async () => {
      console.log("Fetching new data...");
      try {
        const response = await fetch('/api/data');
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        const newData = await response.json();
        console.log("Fetched new data:", newData);
        const sessionArray = newData.SESSION.filter(session => session.SQL_ADDRESS.trim() !== "0") || [];
        setSessionData(sessionArray);

        // 새로운 데이터를 각 차트에 추가
        setData(prevData => {
          const updatedData = [...prevData];
          for (let chartIndex = 0; chartIndex < 6; chartIndex++) {
            checkedStats[chartIndex].forEach((isSelected, statIdx) => {
              if (isSelected) {
                const value = newData.SYSSTAT[statIdx]?.VALUE || 0;
                if (!updatedData[chartIndex][statIdx]) {
                  updatedData[chartIndex][statIdx] = [];
                }
                updatedData[chartIndex][statIdx].push(value);
                if (updatedData[chartIndex][statIdx].length > DATA_POINTS) {
                  updatedData[chartIndex][statIdx].shift();
                }
              }
            });
          }
          return updatedData;
        });

        const currentTime = parseTimeString(newData.TIME.toString());
        const newLabel = currentTime.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: false });
        setLabels(prevLabels => {
          const updatedLabels = [...prevLabels.slice(1), newLabel];
          return updatedLabels;
        });
      } catch (error) {
        console.error("Error fetching data: ", error);

        setData(prevData => {
          const updatedData = [...prevData];
          for (let chartIndex = 0; chartIndex < 6; chartIndex++) {
            checkedStats[chartIndex].forEach((isSelected, statIdx) => {
              if (isSelected) {
                if (!updatedData[chartIndex][statIdx]) {
                  updatedData[chartIndex][statIdx] = [];
                }
                updatedData[chartIndex][statIdx].push(0);
                if (updatedData[chartIndex][statIdx].length > DATA_POINTS) {
                  updatedData[chartIndex][statIdx].shift();
                }
              }
            });
          }
          return updatedData;
        });
      }
    };

    if (intervalRef.current) {
      clearInterval(intervalRef.current);
    }

    intervalRef.current = setInterval(fetchData, 3000);
    
    return () => {
      if (intervalRef.current) {
        clearInterval(intervalRef.current);
      }
    };
  }, [checkedStats]);

  const chartData = (chartIndex) => {
    console.log(`Chart ${chartIndex} Data:`, data[chartIndex]);
    const selectedStatNames = statNames
      .filter((_, idx) => checkedStats[chartIndex][idx])
      .map(stat => stat.name)
      .join(', ') || 'Unknown Stat';

    const datasets = statNames.map((statistic, idx) => {
      if (checkedStats[chartIndex][idx]) {
        const statData = data[chartIndex][idx] || Array(DATA_POINTS).fill(0);

        const colors = [
          'rgba(255, 99, 132, 1)',
          'rgba(54, 162, 235, 1)',
          'rgba(255, 206, 86, 1)',
          'rgba(75, 192, 192, 1)',
          'rgba(153, 102, 255, 1)',
          'rgba(255, 159, 64, 1)'
        ];
        return {
          label: statistic.name,
          data: statData,
          borderColor: colors[idx % colors.length],
          backgroundColor: colors[idx % colors.length].replace('1)', '0.2)'),
          borderWidth: 1,
          tension: 0.4,
          pointRadius: 0,
          pointHoverRadius: 0,
          fill: true,
        };
      } else {
        return null;
      }
    }).filter(dataset => dataset !== null);

    return {
      labels: labels,
      datasets: datasets,
    };
  };

  // 차트 옵션 구성
  const options = {
    responsive: true,
    maintainAspectRatio: false,
    layout: {
      padding: {
        top: 0,
        bottom: 5,
        left: 5,
        right: 5
      }
    },
    plugins: {
      legend: {
        position: 'top',
        align: 'start',
        labels: {
          font: {
            size: 10,
            family: 'Roboto, sans-serif',
            weight: '50',
          },
          color: '#ccc',
          boxWidth: 12,
          padding: 12,
        },
      },
      tooltip: {
        backgroundColor: 'rgba(50, 50, 50, 0.8)',
        titleColor: '#ffffff',
        bodyColor: '#ffffff',
        borderColor: 'rgba(0, 0, 0, 0.1)',
        borderWidth: 1,
        cornerRadius: 4,
        displayColors: false,
        bodyFont: {
          family: 'Roboto, sans-serif',
        },
        titleFont: {
          family: 'Roboto, sans-serif',
        },
      },
    },
    scales: {
      x: {
        ticks: {
          color: '#aaa',
          maxTicksLimit: 10,
          min: 0,
          max: DATA_POINTS - 1,
          font: {
            family: 'Roboto, sans-serif',
            size: 10,
          }
        },
        grid: {
          color: 'rgba(200, 200, 200, 0.2)',
        },
      },
      y: {
        ticks: {
          color: '#aaa',
          font: {
            family: 'Roboto, sans-serif',
            size: 10,
          },
          beginAtZero: true,
          callback: function(value) {
            if (value >= 1000000) {
              return (value / 1000000).toFixed(1) + 'm';
            } else if (value >= 1000) {
              return (value / 1000).toFixed(1) + 'k';
            } else {
              return value;
            }
          },
        },
        grid: {
          color: 'rgba(200, 200, 200, 0.2)',
        },
      },
    },
    animation: {
      duration: 1000,
      easing: 'easeOutCubic',
    }
  };

  // 차트 표시 함수
  const showChart = (index) => {
    setVisibleCharts(prev => {
      const updatedVisibility = [...prev];
      updatedVisibility[index] = true;
      return updatedVisibility;
    });
  };

  // 체크박스 상태 업데이트 핸들러
  const handleCheckboxChange = (chartIndex, statIndex) => {
    setCheckedStats(prev => {
      const updatedCheckedStats = [...prev];
      const currentChartCheckedStats = [...updatedCheckedStats[chartIndex]];
      
      currentChartCheckedStats[statIndex] = !currentChartCheckedStats[statIndex];
      
      updatedCheckedStats[chartIndex] = currentChartCheckedStats;
      return updatedCheckedStats;
    });
  };

  // 드롭다운 토글 핸들러
  const toggleDropdown = (index) => {
    setDropdownOpen(prev => {
      const updated = [...prev];
      updated[index] = !updated[index];
      return updated;
    });
  };

  // 드롭다운 외부 클릭 시 닫히도록 처리
  useEffect(() => {
    const handleClickOutside = (event) => {
      setDropdownOpen(Array(6).fill(false));
    };

    window.addEventListener('click', handleClickOutside);

    return () => {
      window.removeEventListener('click', handleClickOutside);
    };
  }, []);

  return (
    <div className="chart-grid">
      {visibleCharts.map((visible, index) => (
        <div key={index} className="chart-item">
          {visible ? (
            <>
              <div className="chart-wrapper">
                <Line data={chartData(index)} options={options} />
                <div className="dropdown-container">
                  <div
                    className="dropdown-button"
                    onClick={(e) => {
                      e.stopPropagation();
                      toggleDropdown(index);
                    }}
                  >
                    {statNames
                      .filter((_, idx) => checkedStats[index][idx])
                      .map(stat => stat.name)
                      .join(', ') || '선택해 주세요'}
                  </div>
                  {dropdownOpen[index] && (
                    <div
                      className="dropdown-menu"
                      onClick={(e) => e.stopPropagation()}
                    >
                      {statNames.map((statistic, idx) => (
                        <label key={statistic.statisticNo}>
                          <input
                            type="checkbox"
                            checked={checkedStats[index][idx] || false}
                            onChange={() => handleCheckboxChange(index, idx)}
                          />
                          {`${statistic.statisticNo} : ${statistic.name}`}
                        </label>
                      ))}
                    </div>
                  )}
                </div>
              </div>
            </>
          ) : (
            <button className="show-chart-button" onClick={() => showChart(index)}>+</button>
          )}
        </div>
      ))}

      <div className="table-container">
        <table>
          <thead>
            <tr>
              <th>SID</th>
              <th>USERNAME</th>
              <th>STATUS</th>
              <th>SCHEMANAME</th>
              <th>OSUSER</th>
              <th>PROCESS</th>
              <th>MACHINE</th>
              <th>PORT</th>
              <th>PROGRAM</th>
              <th>SQL TEXT</th>
            </tr>
          </thead>
          <tbody>
            {sessionData.map((session, index) => (
              <tr key={index}>
                <td>{session.SID}</td>
                <td>{session.USERNAME}</td>
                <td>{session.STATUS}</td>
                <td>{session.SCHEMANAME}</td>
                <td>{session.OSUSER}</td>
                <td>{session.PROCESS}</td>
                <td>{session.MACHINE}</td>
                <td>{session.PORT}</td>
                <td>{session.PROGRAM}</td>
                <td>{session.SQL_TEXT.length > 100 ? `${session.SQL_TEXT.substring(0, 100)}...` : session.SQL_TEXT}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );
}

export default App;